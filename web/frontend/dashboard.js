const CURRENT_USER = localStorage.getItem("user");
if (!CURRENT_USER) {
  alert("Please login first");
  window.location.href = "index.html";
}
let extractedName = null;

const BASE_URL = "http://localhost:3000";
const urlParams = new URLSearchParams(window.location.search);

// ================= SAFE GET ELEMENT =================
function get(id) {
  return document.getElementById(id);
}

function setActive(element) {
  const items = document.querySelectorAll(".sidebar ul li");

  items.forEach((item) => item.classList.remove("active"));

  element.classList.add("active");
}

// ================= SECTION SWITCHING =================
function showDashboard() {
  if (get("dashboardSection")) get("dashboardSection").style.display = "block";
  if (get("allTransactionsSection"))
    get("allTransactionsSection").style.display = "none";
  if (get("settingsSection")) get("settingsSection").style.display = "none";

  hideAllForms();
}

function showAllTransactions() {
  if (get("dashboardSection")) get("dashboardSection").style.display = "none";
  if (get("allTransactionsSection"))
    get("allTransactionsSection").style.display = "block";
  if (get("settingsSection")) get("settingsSection").style.display = "none";

  loadAllTransactions(); // IMPORTANT
}

function showSettings() {
  if (get("dashboardSection")) get("dashboardSection").style.display = "none";
  if (get("allTransactionsSection"))
    get("allTransactionsSection").style.display = "none";
  if (get("settingsSection")) get("settingsSection").style.display = "block";
}

// ================= FORMS =================
function hideAllForms() {
  if (get("depositForm")) get("depositForm").style.display = "none";
  if (get("withdrawForm")) get("withdrawForm").style.display = "none";
  if (get("transferForm")) get("transferForm").style.display = "none";
}

function showDeposit() {
  showDashboard();
  hideAllForms();
  get("depositForm").style.display = "block";
}

function showWithdraw() {
  showDashboard();
  hideAllForms();
  get("withdrawForm").style.display = "block";
}

function showTransfer() {
  showDashboard();
  hideAllForms();
  get("transferForm").style.display = "block";
}
// ================= BALANCE =================
async function getBalance() {
  let res = await fetch(`${BASE_URL}/balance?user=${CURRENT_USER}`);
  let data = await res.text();
  document.getElementById("balance").innerText = "₹ " + data;
}

// ================= ACTIONS =================
async function depositMoney() {
  let amount = document.getElementById("depositAmount").value;
  if (!amount) return alert("Enter amount");

  await fetch(`${BASE_URL}/deposit?user=${CURRENT_USER}&amount=${amount}`);
  getBalance();
  loadTransactions();
}

async function withdrawMoney() {
  let amount = document.getElementById("withdrawAmount").value;
  if (!amount) return alert("Enter amount");

  await fetch(`${BASE_URL}/withdraw?user=${CURRENT_USER}&amount=${amount}`);
  getBalance();
  loadTransactions();
}

async function transferMoney() {
  let to = document.getElementById("toUser").value;
  let amount = document.getElementById("transferAmount").value;

  if (!to || !amount) return alert("Fill details");

  await fetch(
    `${BASE_URL}/transfer?from=${CURRENT_USER}&to=${to}&amount=${amount}`,
  );
  getBalance();
  loadTransactions();
}

// ================= DATE =================
function formatDateTime(timestamp) {
  let [d, t] = timestamp.split(" ");
  let [y, m, day] = d.split("-");
  let [h, min] = t.split(":");

  let date = `${day}-${m}-${y}`;
  let time = `${h}:${min}`;

  return { date, time };
}

// ================= RECENT =================
async function loadTransactions() {
  let res = await fetch(`${BASE_URL}/transactions?user=${CURRENT_USER}`);
  let data = await res.text();

  let rows = data
    .trim()
    .split("\n")
    .filter((r) => r.trim() !== "")
    .slice(-5)
    .reverse();
  if (rows.length === 0) {
    table.innerHTML = `<tr><td colspan='7'> No transactions found </td></tr>;`;
    return;
  }
  let table = document.getElementById("transactionTable");
  table.innerHTML = "";

  rows.forEach((r) => {
    let [type, amount, balance, time] = r.split(",");

    let name = "Self";
    let id = CURRENT_USER;

    if (type.includes("(")) {
      name = type.match(/\((.*?)\)/)?.[1] || "Self";
      id = type.match(/[A-Z0-9]{6,}/)?.[0] || CURRENT_USER;
    }

    if (type.includes("admin")) {
      name = "Admin";
      id = "SYSTEM";
    }

    let isCredit =
      type.toLowerCase().includes("deposit") ||
      type.toLowerCase().includes("created");

    let txnType = isCredit ? "Credit" : "Debit";
    let f = formatDateTime(time);

    table.innerHTML += `
  <tr>
    <td>${name}</td>
    <td>${id}</td>

    <td class="${isCredit ? "credit" : "debit"}">
      ${txnType}
    </td>

    <td class="${isCredit ? "credit" : "debit"}">
      ${isCredit ? "+ ₹" : "- ₹"}${amount}
    </td>

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

  let rows = data.trim().split("\n").reverse();
  let table = document.getElementById("allTransactionTable");
  table.innerHTML = "";

  rows.forEach((r) => {
    let [type, amount, balance, time] = r.split(",");

    let name = "Self";
    let id = CURRENT_USER;

    if (type.includes("(")) {
      name = type.match(/\((.*?)\)/)?.[1] || "Self";
      id = type.match(/[A-Z0-9]{6,}/)?.[0] || CURRENT_USER;
    }

    if (type.includes("admin")) {
      name = "Admin";
      id = "SYSTEM";
    }

    let isCredit =
      type.toLowerCase().includes("deposit") ||
      type.toLowerCase().includes("created");

    let txnType = isCredit ? "Credit" : "Debit";
    let f = formatDateTime(time);

    table.innerHTML += `
  <tr>
    <td>${name}</td>
    <td>${id}</td>

    <td class="${isCredit ? "credit" : "debit"}">
      ${txnType}
    </td>

    <td class="${isCredit ? "credit" : "debit"}">
      ${isCredit ? "+ ₹" : "- ₹"}${amount}
    </td>

    <td>₹ ${balance}</td>
    <td>${f.date}</td>
    <td>${f.time}</td>
  </tr>
`;
  });
}

// ================= LOGOUT =================
function logout() {
  localStorage.removeItem("user");
  window.location.href = "index.html";
}

// ================= INIT =================
window.onload = function () {
  getBalance();
  loadTransactions();
  document.getElementById("userId").innerText = CURRENT_USER;
};
