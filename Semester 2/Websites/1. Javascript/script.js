
//document.write('meine 1. Ausgabe!');

let h1 = document.getElementById("test");
h1.innerText += " ... Javascript";
h1.style.backgroundColor= "#ccaacc";

let div = document.getElementById("content");
div.innerHTML = 'meine 1. Ausgabe!';

let x = div.innerText;
console.log("x=" +x);

function myFunction(){
    console.log(Date());
}


click();