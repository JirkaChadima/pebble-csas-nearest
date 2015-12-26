'use strict';

var xhrRequest = function (url, type, callback) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        callback(this.responseText);
    };
    xhr.open(type, url);
    console.log('opened');
    xhr.send();
    console.log('sent');
}

function getWeather() {
    navigator.geolocation.getCurrentPosition(
        function (position) {
            var url = 'http://api.openweathermap.org/data/2.5/weather?units=Metric&lat=' + position.coords.latitude + '&lon=' + position.coords.longitude + '&appid=371c06ec7e9768c022f1fee13147a7f5';
            xhrRequest(url, 'GET', function (data) {
                console.log(data);
                var json = JSON.parse(data);
                Pebble.sendAppMessage({
                    'KEY_TEMPERATURE': Math.round(json.main.temp),
                    'KEY_CONDITIONS': json.weather[0].main
                }, function (e) {
                    console.log('sent to pebble');
                }, function (e) {
                    console.log('error sending to pebble');
                });
            });
        },
        function (error) {
            console.log(error);
        },
        {timeout: 15000, maximumAge: 60000}
    );
}

Pebble.addEventListener('ready', function (e) {
    console.log('Pebble JSKit ready')
    getWeather();
});

Pebble.addEventListener('appmessage', function (e) {
    console.log('App message received');
    getWeather();
});