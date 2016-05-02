// Global var
var monthNames = ["Janvier", "Février", "Mars", "Avril", "Mai", "Juin",
  "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"
];

// Personal functions
function pad(num, size) {
    var s = "000000000" + num;
    return s.substr(s.length-size);
}

function dateToString(date) {
    return((date.getDay() + 1) + ((date.getDay() + 1) == 1 ? 'er' : '') + ' ' + monthNames[date.getMonth()] + ' ' + date.getFullYear() + ' à ' + pad(date.getHours(), 2) + 'h' + pad(date.getMinutes(), 2));
}

// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
angular.module('starter', ['ionic', 'chart.js'])

.run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {
    if(window.cordova && window.cordova.plugins.Keyboard) {
      // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
      // for form inputs)
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);

      // Don't remove this line unless you know what you are doing. It stops the viewport
      // from snapping when text inputs are focused. Ionic handles this internally for
      // a much nicer keyboard experience.
      cordova.plugins.Keyboard.disableScroll(true);
    }
    if(window.StatusBar) {
      StatusBar.styleDefault();
    }
  });
})

.config(function ($stateProvider, $urlRouterProvider) {
    $stateProvider
        .state('tabs', {
            url: "/tab",
            templateUrl : "templates/tabs.html",
            abstract : true
        })
        .state('tabs.instantpH', {
            url: "/instantpH",
            views: {
                'instantpH-tab': {
                    templateUrl: "templates/instantpH.html",
                    controller: 'instantpHCtrl'
                }
            }
        })
        .state('tabs.instantTemperature', {
            url: "/instantTemperature",
            views: {
                'instantTemperature-tab': {
                    templateUrl: "templates/instantTemperature.html",
                    controller: 'instantTemperatureCtrl'
                }
            }
        })
        .state('tabs.graphics', {
            url: "/graphics",
            views: {
                'graphics-tab': {
                    templateUrl: "templates/graphics.html",
                    controller: 'graphicsCtrl'
                }
            }
        })
    
    $urlRouterProvider.otherwise('/tab/instantpH')
})

.config(function($ionicConfigProvider) {
    $ionicConfigProvider.tabs.position('bottom');
})

.controller('instantpHCtrl', function($scope, $http) {
    $http.get("http://lepetitvideaste.com/dataToApplication.php?mode=instant&dataType=pH")
    .then(function (response) {
        $scope.pH = response.data.records.Value;
        var date = response.data.records.Date_time;
        // Split timestamp into [ Y, M, D, h, m, s ]
        var t = date.split(/[- :]/);

        // Apply each element to the Date function
        var d = new Date(t[0], t[1]-1, t[2], t[3], t[4], t[5]);
        $scope.date = dateToString(d);
    });
})

.controller('instantTemperatureCtrl', function($scope, $http) {
    $http.get("http://lepetitvideaste.com/dataToApplication.php?mode=instant&dataType=temperature#")
    .then(function (response) {
        $scope.temperature = response.data.records.Value;
        var date = response.data.records.Date_time;
        // Split timestamp into [ Y, M, D, h, m, s ]
        var t = date.split(/[- :]/);

        // Apply each element to the Date function
        var d = new Date(t[0], t[1]-1, t[2], t[3], t[4], t[5]);
        $scope.date = dateToString(d);
    });
    console.log('instantTemperatureCtrl');
})

.controller('graphicsCtrl', function($scope) {
    var ctx = document.getElementById('graphicsChart');
    var data = {
        labels: ["January", "February", "March", "April", "May", "June", "July"],
        datasets: [
            {
                label: "My First dataset",
                fill: false,
                lineTension: 0.1,
                backgroundColor: "rgba(75,192,192,1)",
                borderColor: "rgba(75,192,192,1)",
                borderCapStyle: 'butt',
                borderDash: [],
                borderDashOffset: 0.0,
                borderJoinStyle: 'miter',
                pointBorderColor: "rgba(75,192,192,1)",
                pointBackgroundColor: "#fff",
                pointBorderWidth: 1,
                pointHoverRadius: 5,
                pointHoverBackgroundColor: "rgba(75,192,192,1)",
                pointHoverBorderColor: "rgba(220,220,220,1)",
                pointHoverBorderWidth: 2,
                pointRadius: 1,
                pointHitRadius: 10,
                data: [65, 59, 80, 81, 56, 55, 40],
            },
            {
                label: "My Second dataset",
                fill: false,
                lineTension: 0.1,
                backgroundColor: "rgba(75,192,192,0)",
                borderColor: "rgba(130,30,45,1)",
                borderCapStyle: 'butt',
                borderDash: [],
                borderDashOffset: 0.0,
                borderJoinStyle: 'miter',
                pointBorderColor: "rgba(75,192,192,1)",
                pointBackgroundColor: "#fff",
                pointBorderWidth: 1,
                pointHoverRadius: 5,
                pointHoverBackgroundColor: "rgba(75,192,192,1)",
                pointHoverBorderColor: "rgba(220,220,220,1)",
                pointHoverBorderWidth: 2,
                pointRadius: 1,
                pointHitRadius: 10,
                data: [30, 48, 27, 32, 47, 90, 23],
            }
        ]
    };
    var graphicsChart = new Chart(ctx, {
        type: 'line',
        data: data,
    });
    
    console.log('graphicsCtrl');
});