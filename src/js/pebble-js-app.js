'use strict';

var xhrRequest = function (url, type, key, callback) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        callback(this.status, this.responseText);
    };
    xhr.open(type, url);
    xhr.setRequestHeader('WEB-API-Key', key);
    xhr.send();
}

function getNearestATMs() {
    navigator.geolocation.getCurrentPosition(
        function (position) {
            xhrRequest('https://api.csas.cz/sandbox/webapi/api/v2/places?radius=500&country=CZ&types=ATM&limit=1&lat=' + position.coords.latitude + '&lng=' + position.coords.longitude, 'GET', '7f29f5d5-c9d4-4266-8e6b-3733064da146', function (status, data) {
                console.log(status);
                console.log(data);
                var response = {};
                if (status != 200) {
                    response['KEY_NOT_FOUND'] = true;
                } else {
                    var json = JSON.parse(data).items[0];
                    response = {
                        'KEY_DISTANCE': json.distance,
                        'KEY_DIRECTION': 12, // TODO compute from position.coords.latitude, position.coords.longitude, json.location.lat, json.location.lng
                        'KEY_ADDRESS': json.address + ', ' + json.city,
                        'KEY_ACCESS_TYPE': json.accessType
                    };
                }
                console.log("sending: " + JSON.stringify(response));
                Pebble.sendAppMessage(response);
            });
        },
        function (error) {
            console.log(error);
        },
        {timeout: 15000, maximumAge: 60000}
    );
}

Pebble.addEventListener('ready', function (e) {
    getNearestATMs();
});

//Pebble.addEventListener('appmessage', function (e) {
    //getNearestATMs();
//});
