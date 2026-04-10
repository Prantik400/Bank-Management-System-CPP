const BASE_URL = "http://localhost:3000";

// ================= NAV =================
function hideAll() {
  document.getElementById("createSection").style.display = "none";
  document.getElementById("deleteSection").style.display = "none";
  document.getElementById("allSection").style.display = "none";
  document.getElementById("totalSection").style.display = "none";
}

function showCreate() {
  hideAll();
  document.getElementById("createSection").style.display = "block";
}

function showDelete() {
  hideAll();
  document.getElementById("deleteSection").style.display = "block";
}

function showAll() {
  hideAll();
  document.getElementById("allSection").style.display = "block";
  loadAccounts();
}

function showTotal() {
  hideAll();
  document.getElementById("totalSection").style.display = "block";
  loadTotal();
}

// ================= CREATE =================
async function createAccount() {
  let id = document.getElementById("newId").value;
  let name = document.getElementById("newName").value;
  let pin = document.getElementById("newPin").value;
  let adminPass = prompt("Enter Admin Password");

  if (!id || !name || !pin || !adminPass) return alert("Fill all fields");

  let res = await fetch(
    `${BASE_URL}/create?id=${id}&pin=${pin}&name=${name}&adminPass=${adminPass}`,
  );

  alert(await res.text());
}

// ================= DELETE =================
async function deleteAccount() {
  let id = document.getElementById("deleteId").value;
  let adminPass = prompt("Enter Admin Password");

  if (!id || !adminPass) return alert("Enter ID");

  let res = await fetch(`${BASE_URL}/delete?id=${id}&adminPass=${adminPass}`);

  alert(await res.text());
}

// ================= ALL =================
async function loadAccounts() {
  let adminPass = prompt("Enter Admin Password");
  if (!adminPass) return;

  let res = await fetch(`${BASE_URL}/allAccounts`);
  let data = await res.text();

  let table = document.getElementById("accountsTable");
  table.innerHTML = "";

  data.split("\n").forEach((r) => {
    let [id, name, balance] = r.split(",");

    table.innerHTML += `
      <tr>
        <td>${id}</td>
        <td>${name}</td>
        <td>₹ ${balance}</td>
      </tr>
    `;
  });
}

// ================= TOTAL =================
async function loadTotal() {
  let adminPass = prompt("Enter Admin Password");
  if (!adminPass) return;

  let res = await fetch(`${BASE_URL}/total`);
  let data = await res.text();

  document.getElementById("totalBalance").innerText =
    "₹ " + Number(data).toLocaleString();
}

// ================= LOGOUT =================
function logout() {
  localStorage.clear();
  window.location.href = "index.html";
}

// ================= ACTIVE =================
function setActive(element) {
  const items = document.querySelectorAll(".sidebar ul li");
  items.forEach((i) => i.classList.remove("active"));
  element.classList.add("active");
}
