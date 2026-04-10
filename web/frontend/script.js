const BASE_URL = "http://localhost:3000";

window.onload = function () {
  const params = new URLSearchParams(window.location.search);
  const msg = params.get("msg");

  if (msg) {
    const errorBox = document.getElementById("errorMsg");
    errorBox.style.color = "#22c55e";
    errorBox.innerText = msg;

    // ✅ REMOVE PARAM FROM URL (VERY IMPORTANT)
    window.history.replaceState({}, document.title, "index.html");
  }
};


// ================= GET ELEMENT =================
function get(id) {
  return document.getElementById(id);
}

// ================= ADMIN UI DETECTION =================
get("accountId").addEventListener("input", function () {
  let val = this.value.trim().toLowerCase();
  let container = document.querySelector(".login-container");

  if (val === "admin") {
    container.classList.add("admin-mode");
  } else {
    container.classList.remove("admin-mode");
  }
});

// ================= LOGIN =================
async function login() {
  let id = get("accountId").value.trim();
  let pin = get("pin").value.trim();
  let errorMsg = get("errorMsg");
  let button = document.querySelector("button");

  // RESET
  errorMsg.innerText = "";
  get("accountId").classList.remove("input-error");
  get("pin").classList.remove("input-error");

  // VALIDATION
  if (!id || !pin) {
    errorMsg.innerText = "⚠ Please enter ID and PIN";
    if (!id) get("accountId").classList.add("input-error");
    if (!pin) get("pin").classList.add("input-error");
    return;
  }

  try {
    // LOADING STATE
    button.innerText = "Logging in...";
    button.disabled = true;

    let res = await fetch(`${BASE_URL}/login?user=${id}&pin=${pin}`);
    let data = await res.text();

    console.log("Login Response:", data);

    // RESET BUTTON
    button.innerText = "Login";
    button.disabled = false;

    // ❌ INVALID
    if (data === "INVALID") {
      errorMsg.innerText = "❌ Invalid ID or PIN";
      get("accountId").classList.add("input-error");
      get("pin").classList.add("input-error");
      return;
    }

    // 👑 ADMIN
    if (data === "ADMIN") {
      localStorage.setItem("user", id);
      localStorage.setItem("role", "admin");

      window.location.href = "admin.html";
      return;
    }

    // 👤 USER
    if (data.startsWith("USER:")) {
      let name = data.split(":")[1];

      localStorage.setItem("user", id);
      localStorage.setItem("name", name);
      localStorage.setItem("role", "user");

      window.location.href = "dashboard.html";
    }
  } catch (err) {
    console.error(err);
    errorMsg.innerText = "⚠ Server error. Try again.";
    button.innerText = "Login";
    button.disabled = false;
  }
}

// ================= ENTER KEY =================
document.addEventListener("keydown", function (e) {
  if (e.key === "Enter") {
    login();
  }
});
