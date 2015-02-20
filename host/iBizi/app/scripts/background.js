'use strict';

chrome.runtime.onInstalled.addListener(function (details) {
  console.log('previousVersion', details.previousVersion);
});

chrome.app.runtime.onLaunched.addListener(function() {
	chrome.app.window.create('popup.html', {
    'bounds': {
      'width': 150,
      'height': 190,
    },
    frame:'none'
  });
});
