//Colors array
let colors = ['green', 'red', 'blue','black','purple'];
//get button
let button = document.getElementById('NOTE');
//add event listener
button.addEventListener('click', function(){
    //randomizer
    var randomColor = colors[Math.floor(Math.random() * colors.length)]
    //get container
    let NOTE = document.getElementById('NOTE');

    NOTE.style.background = randomColor;

})
