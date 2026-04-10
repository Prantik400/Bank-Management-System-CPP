// ================= AUTH =================
const CURRENT_USER = localStorage.getItem("user");

if (!CURRENT_USER) {
  alert("Please login first");
  window.location.href = "index.html";
}

// ================= BASE =================
const BASE_URL = "http://localhost:3000";

// ================= HELPER =================
function get(id) {
  return document.getElementById(id);
}

// ================= SIDEBAR =================
function setActive(element) {
  document
    .querySelectorAll(".sidebar ul li")
    .forEach((i) => i.classList.remove("active"));
  element.classList.add("active");
}

// ================= SECTION CONTROL =================
function showDashboard() {
  get("dashboardSection").style.display = "block";
  get("allTransactionsSection").style.display = "none";
  get("settingsSection").style.display = "none";
  hideForms();
}

function showAllTransactions() {
  get("dashboardSection").style.display = "none";
  get("allTransactionsSection").style.display = "block";
  get("settingsSection").style.display = "none";
  loadAllTransactions();
}

function showSettings() {
  get("dashboardSection").style.display = "none";
  get("allTransactionsSection").style.display = "none";
  get("settingsSection").style.display = "block";
}

// ================= FORMS =================
function hideForms() {
  get("depositForm").style.display = "none";
  get("withdrawForm").style.display = "none";
  get("transferForm").style.display = "none";
}

function showDeposit() {
  showDashboard();
  get("depositForm").style.display = "block";
}

function showWithdraw() {
  showDashboard();
  get("withdrawForm").style.display = "block";
}

function showTransfer() {
  showDashboard();
  get("transferForm").style.display = "block";
}

// ================= PIN POPUP =================
function askPin() {
  let pin = prompt("Enter your PIN to continue:");
  if (!pin) {
    alert("PIN required!");
    return null;
  }
  return pin;
}

// ================= BALANCE =================
async function getBalance() {
  try {
    let res = await fetch(`${BASE_URL}/balance?user=${CURRENT_USER}`);
    let data = await res.text();

    get("balance").innerText = "₹ " + data;
  } catch (err) {
    console.error(err);
  }
}

// ================= ACTIONS =================
async function depositMoney() {
  let amount = get("depositAmount").value;

  if (!amount || amount <= 0) return alert("Enter valid amount");

  let pin = askPin();
  if (!pin) return;

  let res = await fetch(
    `${BASE_URL}/deposit?user=${CURRENT_USER}&amount=${amount}&pin=${pin}`,
  );

  let data = await res.text();
  alert(data);

  get("depositAmount").value = "";

  getBalance();
  loadTransactions();
}

async function withdrawMoney() {
  let amount = get("withdrawAmount").value;

  if (!amount || amount <= 0) return alert("Enter valid amount");

  let pin = askPin();
  if (!pin) return;

  let res = await fetch(
    `${BASE_URL}/withdraw?user=${CURRENT_USER}&amount=${amount}&pin=${pin}`,
  );

  let data = await res.text();
  alert(data);

  get("withdrawAmount").value = "";

  getBalance();
  loadTransactions();
}

async function transferMoney() {
  let to = get("toUser").value;
  let amount = get("transferAmount").value;

  if (!to || !amount || amount <= 0) return alert("Fill details");

  let pin = askPin();
  if (!pin) return;

  let res = await fetch(
    `${BASE_URL}/transfer?from=${CURRENT_USER}&to=${to}&amount=${amount}&pin=${pin}`,
  );

  let data = await res.text();
  alert(data);

  get("toUser").value = "";
  get("transferAmount").value = "";

  getBalance();
  loadTransactions();
}

// ================= FORMAT =================
function formatDateTime(timestamp) {
  try {
    let [d, t] = timestamp.split(" ");
    let [y, m, day] = d.split("-");
    let [h, min] = t.split(":");

    return {
      date: `${day}-${m}-${y}`,
      time: `${h}:${min}`,
    };
  } catch {
    return { date: "-", time: "-" };
  }
}

// ================= PARSER =================
function parseTransaction(type) {
  let name = "Self";
  let id = CURRENT_USER;

  if (type.includes("(")) {
    name = type.match(/\((.*?)\)/)?.[1] || "Self";
    id = type.match(/[A-Z0-9]{4,}/)?.[0] || CURRENT_USER;
  }

  if (type.toLowerCase().includes("admin")) {
    name = "Admin";
    id = "SYSTEM";
  }

  return { name, id };
}

function isCreditType(type) {
  type = type.toLowerCase();

  return (
    type.includes("deposit") ||
    type.includes("received") ||
    type.includes("created")
  );
}

// ================= RECENT =================
async function loadTransactions() {
  let res = await fetch(`${BASE_URL}/transactions?user=${CURRENT_USER}`);
  let data = await res.text();

  let table = get("transactionTable");
  table.innerHTML = "";

  let rows = data
    .trim()
    .split("\n")
    .filter((r) => r.trim() !== "")
    .slice(-5)
    .reverse();

  if (rows.length === 0) {
    table.innerHTML = `<tr><td colspan="7">No transactions</td></tr>`;
    return;
  }

  rows.forEach((r) => {
    let [type, amount, balance, time] = r.split(",");

    let { name, id } = parseTransaction(type);
    let isCredit = isCreditType(type);
    let f = formatDateTime(time);

    table.innerHTML += `
      <tr>
        <td>${name}</td>
        <td>${id}</td>
        <td>${isCredit ? "Credit" : "Debit"}</td>
        <td>${isCredit ? "+ ₹" : "- ₹"}${amount}</td>
        <td>₹ ${balance}</td>
        <td>${f.date}</td>
        <td>${f.time}</td>
      </tr>
    `;
  });
}

// ================= ALL =================
async function loadAllTransactions() {
  let res = await fetch(`${BASE_URL}/transactions?user=${CURRENT_USER}`);
  let data = await res.text();

  let table = get("allTransactionTable");
  table.innerHTML = "";

  let rows = data.trim().split("\n").reverse();

  rows.forEach((r) => {
    let [type, amount, balance, time] = r.split(",");

    let { name, id } = parseTransaction(type);
    let isCredit = isCreditType(type);
    let f = formatDateTime(time);

    table.innerHTML += `
      <tr>
        <td>${name}</td>
        <td>${id}</td>
        <td>${isCredit ? "Credit" : "Debit"}</td>
        <td>${isCredit ? "+ ₹" : "- ₹"}${amount}</td>
        <td>₹ ${balance}</td>
        <td>${f.date}</td>
        <td>${f.time}</td>
      </tr>
    `;
  });
}

// ================= CHANGE PIN =================
async function changePin() {
  let oldPin = get("oldPin").value;
  let newPin = get("newPin").value;

  if (!oldPin || !newPin) return alert("Enter all fields");

  let res = await fetch(
    `${BASE_URL}/changePin?user=${CURRENT_USER}&oldPin=${oldPin}&newPin=${newPin}`,
  );

  let data = await res.text();

  alert(data);

  if (data.toLowerCase().includes("success")) {
    logout();
  }
}

// ================= LOGOUT =================
function logout() {
  localStorage.clear();
  window.location.href = "index.html";
}

// ================= INIT =================
window.onload = () => {
  getBalance();
  loadTransactions();

  get("username").innerText = localStorage.getItem("name") || "User";

  get("userId").innerText = CURRENT_USER;
};
