const fs = require('fs');
const readline = require('readline');

const MIN_JUMP = 1;
const MAX_JUMP = 3;

function isSafeReportasd(report) {
    if (report[0] > report[1]) {
        for (let i = 0; i < report.length - 1; i++) {
            const current = report[i];
            const next = report[i + 1];
            if (current - next < MIN_JUMP || current - next > MAX_JUMP) {
                return false;
            }
        }
    } else {
        for (let i = 0; i < report.length - 1; i++) {
            const current = report[i];
            const next = report[i + 1];
            if (current - next > -MIN_JUMP || current - next < -MAX_JUMP) {
                return false;
            }
        }
    }
    return true;
    
}



function checkDiff(report) {
    for (let i = 0; i < report.length - 1; i++) {
        const current = report[i];
        const next = report[i + 1];
        if (Math.abs(current - next) < MIN_JUMP || Math.abs(current - next) > MAX_JUMP) {
            return false;
        }
    }
    return true;
}

function isSorted(report) {
    if (report[0] > report[1]) {
        for (let i = 0; i < report.length - 1; i++) {
            const current = report[i];
            const next = report[i + 1];
            if (current < next) {
                return false;
            }
        }
    } else {
        for (let i = 0; i < report.length - 1; i++) {
            const current = report[i];
            const next = report[i + 1];
            if (current > next) {
                return false;
            }
        }
    }
    return true;
}

function isSafeReport(report){
    console.log("🚀 ~ isSafeReport ~ report:", report)
    return isSorted(report) && checkDiff(report);
};

function isSafeReport2(report) {
    console.log("🚀 ~ isSafeReport2 ~ report:", report)
    if (isSafeReport(report)) {
        return [true];
    }
    for (let i = 0; i < report.length; i++) {
        if (isSafeReport(report.toSpliced(i,1))) {
            return [true, true];
        }
    }
    return [false]
}

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });
    let safeReportCount = 0;
    lines = 0;
    for await (const line of rl) {
        lines++;
        const report = line.replace(/\s+/g, ' ').split(' ').map(Number);
        const [safe, levelRemoved] = isSafeReport2(report);
        if (safe) {
            if (levelRemoved) {
                console.log("🚀 ~ safe level removed\t ~ report:\n", report)
            } else {
                console.log("🚀 ~ safe\t ~ report:\n", report)
            }
            
            safeReportCount++;
        } else {
            console.log("🚀 ~ unsafe\t ~ report:\n", report)
        }
            
    }
    console.log("🚀 ~ Result:", safeReportCount)
    console.log("🚀 ~ lines:", lines)
  }

  
  processLineByLine();

  
