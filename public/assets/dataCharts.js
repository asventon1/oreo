let totalDistanceLable = document.getElementById('totalDistance');
var ctx = document.getElementById('myChart').getContext('2d');
var chart = new Chart(ctx, {
    // The type of chart we want to create
    type: 'line',

    // The data for our dataset
    data: {
        labels: [],
        datasets: [{
            label: 'Number of rotations',
            backgroundColor: 'rgb(0, 0, 0, 0)',
            borderColor: 'rgb(255, 99, 132)',
            data: []
        }]
    },

    // Configuration options go here
    options: {}
});

fetch("http://192.168.150.2:3000/rpmdata").then(function(response) {
    response.text().then(function(text) {
        let rpmData = JSON.parse(text);
        let newTime = [];
        rpmData.time.forEach(function(v){
            newTime.push(new Date(v*1000).toLocaleString());
        });
        if(chart.data.labels != newTime || chart.data.datasets[0].data != rpmData.rpm){
            chart.data.labels = newTime;
            chart.data.datasets[0].data = rpmData.rpm;
            chart.update();
            let totalRotations = 0;
            rpmData.rpm.forEach(function(v){
                totalRotations+=v;
            });
            totalDistanceLable.innerHTML = `The total distance travled is ${totalRotations*37.69908/12} feet or ${totalRotations*37.69908/12/5280} miles`;
        }
    });
});