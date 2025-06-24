// scripts.js

// 1) MENU RESPONSIVO: Toggle en menú móvil
document.addEventListener('DOMContentLoaded', () => {
  const chk = document.getElementById('menu');
  const nav = document.querySelector('.navbar');
  chk.addEventListener('change', () => {
    nav.style.display = chk.checked ? 'block' : 'none';
  });
});

// 2) FORMULARIO DE RESERVAS: Validación básica
window.addEventListener('load', () => {
  const form = document.getElementById('reservaForm');
  if (!form) return;
  form.addEventListener('submit', e => {
    e.preventDefault();
    // Recolectar campos
    const nombre = form.nombre.value.trim();
    const email  = form.email.value.trim();
    const fechaIn = form.checkin.value;
    const fechaOut= form.checkout.value;
    if (!nombre || !email || !fechaIn || !fechaOut) {
      alert('Por favor completa todos los campos.');
      return;
    }
    // Aquí podrías enviar datos a tu servidor con fetch()
    alert(`Gracias, ${nombre}! Tu reserva de ${fechaIn} a ${fechaOut} ha sido recibida.`);
    form.reset();
  });
});

// 3) BOTONES ACTIVO/DESACTIVO
document.addEventListener('click', e => {
  if (e.target.classList.contains('btn-1')) {
    e.target.classList.toggle('active');
    // .active puede definir otro color o sombra en CSS
  }
});
