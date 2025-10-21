document.addEventListener('DOMContentLoaded', function() {
    let html = document.documentElement; // Get reference to <html> element
    let bt = document.getElementById('ToggleTheme');
    
    bt.addEventListener('click', function(event) {
        if (html.dataset.bsTheme === 'light') {
            html.dataset.bsTheme = 'dark';
        } else {
            html.dataset.bsTheme = 'light';
        }
    });
});