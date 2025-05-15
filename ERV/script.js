const menuHamburger = document.querySelector(".menu_burger")
const onglets = document.querySelector(".onglets")
const btn_reset = document.querySelector('.btn_reset');

menuHamburger.addEventListener('click', () => {
    onglets.classList.toggle('fermer_onglets')
})
btn_reset.addEventListener('click', () => {
    window.scrollTo({top: 0,left: 0,})
})