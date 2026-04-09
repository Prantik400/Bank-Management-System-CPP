const express = require("express");
const { exec } = require("child_process");
const path = require("path");

const app = express();
const PORT = 3000;

app.use(express.static("web/frontend"));
// Path to your C++ exe
const exePath = path.join(__dirname, "web/backend/api.exe");

// 🔹 Helper function to run C++ inside MinGW bash
function runCpp(command, callback) {
  exec(`cmd /c "${exePath}" ${command}`, (error, stdout, stderr) => {
    console.log("STDOUT:", stdout);
    console.log("STDERR:", stderr);

    if (error) {
      return callback(stdout || "ERROR");
    }
    callback(stdout.trim());
  });
}

// ===============================
// ✅ ROUTES
// ===============================

// 🔹 Get Balance
app.get("/balance", (req, res) => {
  const user = req.query.user;

  runCpp(`balance ${user}`, (result) => {
    res.send(result);
  });
});

// 🔹 Deposit
app.get("/deposit", (req, res) => {
  const user = req.query.user;
  const amount = req.query.amount;

  runCpp(`deposit ${user} ${amount}`, (result) => {
    res.send(result);
  });
});

// 🔹 Withdraw
app.get("/withdraw", (req, res) => {
  const user = req.query.user;
  const amount = req.query.amount;

  runCpp(`withdraw ${user} ${amount}`, (result) => {
    res.send(result);
  });
});

// 🔹 Transfer
app.get("/transfer", (req, res) => {
  const from = req.query.from;
  const to = req.query.to;
  const amount = req.query.amount;

  runCpp(`transfer ${from} ${to} ${amount}`, (result) => {
    res.send(result);
  });
});

//Transaction
app.get("/transactions", (req, res) => {
  const user = req.query.user;

  runCpp(`transactions ${user}`, (result) => {
    res.send(result);
  });
});

// ===============================
// ✅ START SERVER
// ===============================
app.listen(PORT, () => {
  console.log(`🚀 Server running on http://localhost:${PORT}`);
});
