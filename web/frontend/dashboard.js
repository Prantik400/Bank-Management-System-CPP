// Hide all forms first
function hideAllForms() {
  document.getElementById("depositForm").style.display = "none";
  document.getElementById("withdrawForm").style.display = "none";
  document.getElementById("transferForm").style.display = "none";
}

// Show specific form
function showDeposit() {
  hideAllForms();
  document.getElementById("depositForm").style.display = "block";
}

function showWithdraw() {
  hideAllForms();
  document.getElementById("withdrawForm").style.display = "block";
}

function showTransfer() {
  hideAllForms();
  document.getElementById("transferForm").style.display = "block";
}

// Sidebar active highlight
const menuItems = document.querySelectorAll(".sidebar ul li");

menuItems.forEach((item) => {
  item.addEventListener("click", () => {
    menuItems.forEach((i) => i.classList.remove("active"));
    item.classList.add("active");
  });
});

async function getBalance() {
  let response = await fetch("http://localhost:3000/balance?user=ABCD1234");
  let data = await response.text();

  document.querySelector(".balance-card h2").innerText = "₹ " + data;
}

window.onload = function () {
  getBalance();
};