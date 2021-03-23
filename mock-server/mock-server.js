const net = require('net');
let count = 0;
let interval;

function createMockBinaryBytes(length) {
    let returnString = "";
    for(let i = 0; i < length; i++ ) {
        for(let j = 0; j < 8; j++){
            returnString += Math.round(Math.random()); //return random 0 or 1
        }
    }
    return returnString;
}

// creates the TCP server
const server = net.createServer((socket) => {
    socket.on('data', (data) =>{
        console.log(data.toString());
    })

    socket.write('[SERVER]: Hello, you are now connected to the TCP server');
    interval = setInterval(()=>intervalFunction(socket), 1000);

    // gets called when a client disconnects
    socket.on('close', () =>{
        console.log("A client has disconnected");
        closeInterval();
    })

    // gets called when there is an error
    socket.on('error', (err) =>{
        console.log("AN ERROR HAS OCCURED");
        closeInterval();
        console.log(err);
    });
})

// gets called when a client connects
server.on('connection', (data) => {
    console.log("A client has connected to the server: " + data.remoteAddress);
    count = 0;
})

// gets called when the server opens and sets port
server.listen(9898, () => {
    console.log('opened server on', server.address().port);
})

// is the function that gets called every second and returns it to the client
function intervalFunction(socket) {
    socket.write(createMockBinaryBytes(8));
}

function closeInterval() {
    if(interval) {
        clearInterval(interval);
    }
}
