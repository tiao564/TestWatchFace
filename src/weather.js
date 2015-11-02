

// Listen for when AppMessage is received
Pebble.addEventListener('appmessage', 
  function(e){
    console.log('AppMessage received!');
  }
);

function locationSucess(pos){
  // We will the weather here
}

function locationError(err){
  console.log('Error requesting location!');
}

function getWeather(){
  navigator.geolocation.getCurrentPosition(
  locationSuccess,
  locationError,
    {timeout:15000, maximumAge: 60000}
  );
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready',
  function(e) {
    console.log('PebbleKit JS ready!');
    
    // Get inital weather
    getWeather();
  }
);

var xhrRequest = function(url, type, callback){
  var xhr = new XMLHttpRequest();
  xhr.onload = function() {
    callback(this.responseText);
  };
  xhr.open(type,url);
  xhr.send();
};
function locationSuccess(pos){
var url = 'http://api.openweathermap.org/data/2.5/weather?lat=' + pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=' + myAPIKey;

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', function(responseText){
    // responseText contains a JSON object with weather info
    var json = JSON.parse(responseText);
    // got temp in kalvins
    var temperature = Math.round(json.main.temp - 273.15);
    console.log('Temperature is ' + temperature);
    
    // Conditions
    var conditions = json.weather[0].main;
    console.log('Conditions are ' + conditions);
    }
  );
}

