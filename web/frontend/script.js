const BASE_URL = "http://localhost:3000";

// 👁 SHOW / HIDE PASSWORD
function togglePassword() {
  let pinInput = document.getElementById("pin");

  if (pinInput.type === "password") {
    pinInput.type = "text";
  } else {
    pinInput.type = "password";
  }
}

// 🔐 LOGIN FUNCTION
async function login() {
  let id = document.getElementById("accountId").value.trim();
  let pin = document.getElementById("pin").value.trim();
  let error = document.getElementById("errorMsg");

  // RESET ERROR
  error.innerText = "";

  // ✅ VALIDATION
  if (!id || !pin) {
    error.innerText = "⚠️ Please fill all fields";
    return;
  }

  if (pin.length < 4) {
    error.innerText = "⚠️ PIN must be at least 4 digits";
    return;
  }

  try {
    // 🔥 BACKEND LOGIN API (you can change endpoint later)
    let response = await fetch(`${BASE_URL}/login?user=${id}&pin=${pin}`);

    let result = await response.text();

    // ❌ INVALID LOGIN
    if (result.toLowerCase().includes("invalid")) {
      error.innerText = "❌ Invalid ID or PIN";
      return;
    }

    // ✅ SUCCESS
    localStorage.setItem("user", id); // save user
    window.location.href = "dashboard.html";
  } catch (err) {
    error.innerText = "⚠️ Server error. Try again.";
    console.error(err);
  }
}

// 🔄 ENTER KEY SUPPORT
document.addEventListener("keypress", function (e) {
  if (e.key === "Enter") {
    login();
  }
});
