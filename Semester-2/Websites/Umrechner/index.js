var input = document.getElementById("input");
var output = document.getElementById("output");
var unit1 = document.getElementById("unit1");
var unit2 = document.getElementById("unit2");
function cmToInch() {
    if (input !== null && output !== null) {
        var result = Number(input.value) / 2.54;
        output.value = String(result);
        unit1.innerHTML = "cm";
        unit2.innerHTML = "inch";
    }
}
function inchToCm() {
    if (input !== null && output !== null) {
        var result = Number(input.value) * 2.54;
        output.value = String(result);
        unit1.innerHTML = "inch";
        unit2.innerHTML = "cm";
    }
}
function meterToYard() {
    if (input !== null && output !== null) {
        var result = Number(input.value) * 1.09361;
        output.value = String(result);
        unit1.innerHTML = "metets";
        unit2.innerHTML = "yards";
    }
}
function yardToMeter() {
    if (input !== null && output !== null) {
        var result = Number(input.value) / 1.09361;
        output.value = String(result);
        unit1.innerHTML = "yards";
        unit2.innerHTML = "meters";
    }
}
