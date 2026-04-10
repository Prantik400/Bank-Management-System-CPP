const express = require("express");
const { spawn } = require("child_process");
const path = require("path");

const app = express();
const PORT = 3000;

app.use(express.static("web/frontend"));

const exePath = path.join(__dirname, "web/backend/api.exe");

// ================= CORE RUN FUNCTION =================
function runCppInteractive(args, inputs, callback) {
  const process = spawn(exePath, args);

  let output = "";
  let errorOutput = "";

  process.stdout.on("data", (data) => {
    output += data.toString();
  });

  process.stderr.on("data", (data) => {
    errorOutput += data.toString();
  });

  process.on("close", () => {
    console.log("CMD:", args.join(" "));
    console.log("OUTPUT:", output);
    console.log("ERROR:", errorOutput);

    callback(output.trim());
  });

  // 🔥 simulate user input
  if (inputs && inputs.length > 0) {
    inputs.forEach((input) => {
      process.stdin.write(input + "\n");
    });
  }

  process.stdin.end();
}

// ================= LOGIN =================
app.get("/login", (req, res) => {
  const { user, pin } = req.query;

  runCppInteractive(["login"], [user, pin], (result) => {
    res.send(result || "INVALID");
  });
});

// ================= BALANCE =================
app.get("/balance", (req, res) => {
  const { user } = req.query;

  runCppInteractive(["balance"], [user], (result) => {
    res.send(result || "0");
  });
});

// ================= DEPOSIT =================
app.get("/deposit", (req, res) => {
  const { user, amount, pin } = req.query;

  runCppInteractive(["deposit"], [user, amount, pin], (result) => {
    res.send(result);
  });
});

// ================= WITHDRAW =================
app.get("/withdraw", (req, res) => {
  const { user, amount, pin } = req.query;

  runCppInteractive(["withdraw"], [user, amount, pin], (result) => {
    res.send(result);
  });
});

// ================= TRANSFER =================
app.get("/transfer", (req, res) => {
  const { from, to, amount, pin } = req.query;

  runCppInteractive(["transfer"], [from, to, amount, pin], (result) => {
    res.send(result);
  });
});

// ================= TRANSACTIONS =================
app.get("/transactions", (req, res) => {
  const { user } = req.query;

  runCppInteractive(["transactions"], [user], (result) => {
    res.send(result || "");
  });
});

// ================= CHANGE PIN =================
app.get("/changePin", (req, res) => {
  const { user, oldPin, newPin } = req.query;

  runCppInteractive(["changePin"], [user, oldPin, newPin, newPin], (result) => {
    res.send(result);
  });
});

// ================= ADMIN =================

// CREATE ACCOUNT
app.get("/create", (req, res) => {
  const { id, name, pin } = req.query;

  runCppInteractive(
    ["create"],
    [id, name, "0", pin, pin, "admin123"],
    (result) => {
      res.send(result);
    },
  );
});

// DELETE ACCOUNT
app.get("/delete", (req, res) => {
  const { id } = req.query;

  runCppInteractive(["delete"], [id, "admin123"], (result) => {
    res.send(result);
  });
});

// ALL ACCOUNTS
app.get("/allAccounts", (req, res) => {
  runCppInteractive(["allAccounts"], ["admin123"], (result) => {
    res.send(result);
  });
});

// TOTAL
app.get("/total", (req, res) => {
  runCppInteractive(["total"], ["admin123"], (result) => {
    res.send(result);
  });
});

// ================= START =================
app.listen(PORT, () => {
  console.log(`🚀 Server running on http://localhost:${PORT}`);
});
