'use strict';

(function(){

	var colorMap = {};
	colorMap.red = '#ff0000';
	colorMap.blue = '#0000ff';
	colorMap.green = '#00ff00';
	colorMap.yellow = '#ffff00';
	colorMap.orange = '#ffaa00';
	colorMap.pink = '#fe01b1';
	colorMap.cyan = '#00ffff';
	colorMap.available = colorMap.green;
	colorMap.busy = colorMap.red;

	var isConnected = false;
	var currentColor = '#00ff00';
	var isOn = true;
	var lastColor = currentColor;
	var exitOnBlur = true;

	var app = angular.module('ibizApp', ['colorpicker.module']);

	app.directive('setColor', function() {
		return {
			restrict: 'A',
			link: function(scope, element, attr) {
				element.css('background-color', attr.setColor);
				element.on('click', function() {
					if(!scope.ledCtrl.isOn) { return; }
					scope.ledCtrl.currentColor = attr.setColor;
					scope.$apply();
				});
			}
		};
	});

	app.directive('selectOnClick', function () {
	    return {
	        restrict: 'A',
	        link: function (scope, element, attrs) {
	            element.on('click', function () {
	                this.select();
	            });
	        }
	    };
	});

	app.controller('LedController', ['$scope', function($scope){
		this.currentColor = currentColor;
		this.isConnected = isConnected;
		this.isOn = isOn;
		this.exitOnBlur = exitOnBlur;
		this.myVal = 0;

		var scope = this;

		$scope.$watch('ledCtrl.currentColor', function(newVal){
			scope.sendColor();
		});

		this.sendColor = function() {
			if(!this.isOn) {
				return;
			}
			this.connectAndSendColor(this.currentColor);
		};

		this.blur = function() {
			if(scope.exitOnBlur) {
				chrome.app.window.current().close();
			}
		};

		this.toggleOnOff = function() {
			if(this.isOn) {
				lastColor = this.currentColor;
				this.currentColor = '#000000';
				this.sendColor();
				this.isOn = false;
			} else{
				this.currentColor = lastColor;
				this.isOn = true;
			}
		};

		this.connectAndSendColor = function(colorString) {
			chrome.hid.getDevices({'vendorId': 1003, 'productId' : 8271}, function(devices){
				if (!devices || devices.length === 0) {
					return;
				}

				// connect to first device found
				var deviceInfo = devices[0];

				chrome.hid.connect(deviceInfo.deviceId, function(connectInfo) {
					if (!connectInfo) {
						console.warn('Unable to connect to device.');
					}
					var connId = connectInfo.connectionId;

					if(connId >= 0) {

						var red = parseInt(colorString.substring(1,3),16);
						var grn = parseInt(colorString.substring(3,5),16);
						var blu = parseInt(colorString.substring(5,7),16);

						var command = [red, grn, blu, 0xff, 0xff, 0, 0, 0];
						var bytes = new Uint8Array(command);

						chrome.hid.send(connId, 0, bytes.buffer, function() {
							chrome.hid.disconnect(connId);
						});
					}
				});
			});

		};

		this.messageHandler = function(request, sender, sendResponse) {
			if(sender.id === 'ijlohjapdhdmmngalehjpopbickhboim')
			{
				if(request.ping) {
					sendResponse( { isActive : true } );
					return;
				}

				var input = request.input;
				if(colorMap.hasOwnProperty(input))
				{
					scope.currentColor = colorMap[input];
				}
				else {

					if(input[0] !== '#') {
						input = '#' + input;
					}
					scope.currentColor = input;
				}
				
				$scope.$apply();
			}
		};
		

		this.init = function() {
			chrome.app.window.current().contentWindow.onblur = this.blur;
			chrome.runtime.onMessageExternal.addListener(this.messageHandler);
			console.log('listening...');
		};
		
		this.init();
	}]);
})();