
let matrix = [];
let anim = "";
let hexOut = "";

function main() {
    for (let i = 0; i < 8; i++) {
        matrix[i] = [];
        for (let j = 0; j < 8; j++) {
            matrix[i][j] = 0;
            document.getElementById(`cell_${i}-${j}`).onclick = cellOnClick;
        }
    }

    document.getElementById("file").onchange = handleFileSelect;
    document.getElementById("addFrame").onclick = handleFrameAdd;
    document.getElementById("open").onclick = (e) => {
        document.getElementById("file").click();
        e.preventDefault();
    };

    updateOut();
}

function handleFileSelect(e) {
    let file = e.target.files[0]; // FileList object

    let reader = new FileReader();
    reader.onload = (e) => {
        processOpenedFile(e.target.result);
    };

    reader.readAsText(file);
}

function handleFrameAdd(e) {
    anim += hexOut;
    document.getElementById("anim").innerText = anim;
    e.preventDefault();
}

function processOpenedFile(data) {
    let pairs = [];
    for(let i = 0; i < data.length; i += 2) {
        pairs[pairs.length] = data.substr(i, 2);
    }

    for (let i = 0; i < 8; i++) {
        let bits = "";
        let n = parseInt(pairs[i], 16);

        for (let i = 128; i >= 1; i /= 2) {
            bits += n & i ? '1' : '0';
        }

        for (let z = 0; z < 8; z++) {
            matrix[i][z] = parseInt(bits.charAt(z), 10);
        }
    }

    updateOut(true);
}

function cellOnClick(e) {
    let id = e.srcElement.id;
    let cord = id.split("_")[1].split("-");
    let x = cord[0];
    let y = cord[1];

    if (matrix[x][y] === 0) {
        e.srcElement.classList.add("cell-active");
        matrix[x][y] = 1;
    } else {
        e.srcElement.classList.remove("cell-active");
        matrix[x][y] = 0;
    }

    updateOut();
}

function updateOut(redraw) {
    let hexString = "";
    hexOut = "";

    for (let i = 0; i < 8; i++) {
        let binString = "";

        for (let j = 0; j < 8; j++) { //for (let j = 7; j >= 0; j--) {
            binString += matrix[i][j];

            if (redraw) {
                let elem = document.getElementById(`cell_${i}-${j}`);
                if (matrix[i][j] === 0) {
                    elem.classList.remove("cell-active");
                } else {
                    elem.classList.add("cell-active");
                }
            }
        }


        let n = parseInt(binString, 2).toString(16).toUpperCase();
        if (n.length === 1)
            n = "0" + n;

        document.getElementById(`hexLabel-${i}`).innerHTML = n;
        document.getElementById(`binLabel-${i}`).innerHTML = binString;
        hexString += n;
        hexOut += n;
    }

    document.getElementById("download").href = `data:text/plain;charset=utf-8,%EF%BB%BF${encodeURIComponent(hexOut)}`;
    document.getElementById("out").innerText = hexString;

}
function startDrawing()
{
    alert("Start drawing");
}
