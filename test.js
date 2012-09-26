var addon = require('./build/Release/farm');

function test(arg){
    console.log(arg.Name())
    arg.move()
}

var obj = new addon.Dog("Cool Dog");
test(obj)
