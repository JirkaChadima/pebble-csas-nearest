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

// http://gis.stackexchange.com/questions/29239/calculate-bearing-between-two-decimal-gps-coordinates
function radians(n) {
    return n * (Math.PI / 180);
}

function degrees(n) {
    return n * (180 / Math.PI);
}

function computeBearing(source, destination) {
    var startLat = radians(source.latitude),
        startLong = radians(source.longitude),
        endLat = radians(destination.latitude),
        endLong = radians(destination.longitude),
        dLong = endLong - startLong,
        dPhi = Math.log(Math.tan(endLat/2.0+Math.PI/4.0)/Math.tan(startLat/2.0+Math.PI/4.0));

  if (Math.abs(dLong) > Math.PI){
    if (dLong > 0.0)
       dLong = -(2.0 * Math.PI - dLong);
    else
       dLong = (2.0 * Math.PI + dLong);
  }

  return Math.round((degrees(Math.atan2(dLong, dPhi)) + 360.0) % 360.0);
}

function getNearestATMs() {
    navigator.geolocation.getCurrentPosition(
        function (position) {
            xhrRequest('https://api.csas.cz/sandbox/webapi/api/v2/places?radius=500&country=CZ&types=ATM&limit=1&lat=' + position.coords.latitude + '&lng=' + position.coords.longitude, 'GET', '7f29f5d5-c9d4-4266-8e6b-3733064da146', function (status, data) {
                console.log(JSON.stringify(position.coords));
                console.log(status);
                console.log(data);
                var response = {};
                if (status != 200) {
                    response['KEY_NOT_FOUND'] = true;
                } else {
                    var json = JSON.parse(data).items[0];
                    response = {
                        'KEY_DISTANCE': json.distance,
                        'KEY_DIRECTION': computeBearing(position.coords, {
                            latitude: json.location.lat,
                            longitude: json.location.lng
                        }),
                        'KEY_ADDRESS': json.address + '\n' + json.city,
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

Pebble.addEventListener('appmessage', function (e) {
    getNearestATMs();
});
