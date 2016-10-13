'use strict';

var appId = 'chneagfdpnefonnnhmfmhafmnjekhegi';
var textToSend = '';

var launchApp = function(callback)
{
	chrome.management.launchApp(appId, callback);
};

var sendInputMessage = function () {
	chrome.runtime.sendMessage(appId, {'input': textToSend});
};

var checkIfAlive = function (callback) {
	chrome.runtime.sendMessage(appId, {'ping': true}, function (response) {
		if(response && response.isActive === true) {
			callback(true);
		}
		else {
			callback(false);
		}
	});
};

chrome.runtime.onInstalled.addListener(function (details) {
  console.log('previousVersion', details.previousVersion);
});

chrome.browserAction.onClicked.addListener(function(){
	launchApp();
});

chrome.omnibox.onInputEntered.addListener( function (text) {

	textToSend = text;
	
	checkIfAlive(function (isAlive){
		if (isAlive) {
			sendInputMessage();
		} else {
			launchApp( function () {
				setTimeout(sendInputMessage, 1000); // seems like a hack... is there a better way?
			});
		}
	});
});
