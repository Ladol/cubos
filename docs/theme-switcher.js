document.addEventListener('DOMContentLoaded', function() {
    const buttons = document.querySelectorAll('.theme-button');
    const root = document.documentElement;

    // Load saved theme
    const savedTheme = localStorage.getItem('theme') || 'dark';
    setTheme(savedTheme);

    buttons.forEach(button => {
        button.addEventListener('click', () => {
            const theme = button.dataset.theme;
            setTheme(theme);
            localStorage.setItem('theme', theme);
            console.log("Theme is now set to: " + theme);
        });
    });

    function setTheme(theme) {
        // Remove active class from all buttons
        buttons.forEach(btn => btn.classList.remove('active'));
        
        // Add active class to selected theme button
        const activeButton = document.querySelector(`.theme-button.${theme}`);
        if (activeButton) {
            activeButton.classList.add('active');
        }

        // Set theme attribute
        root.setAttribute('data-theme', theme);

        // Force style update by triggering a reflow
        void root.offsetHeight;

        // Update CSS variables based on theme
        if (theme === 'dark') {
            root.style.setProperty('--m-primary', '#00BFFF');
            root.style.setProperty('--m-background-color', '#202325');
            root.style.setProperty('--m-text-color', '#D9DDDE');
            root.style.setProperty('--m-sidebar-background', '#25313C');
            root.style.setProperty('--m-code-background', '#222A31');
            root.style.setProperty('--m-navbar-background', '#22272E');
            root.style.setProperty('--m-footer-background', '#2A2F36');
        } else if (theme === 'gray') {
            root.style.setProperty('--m-primary', '#00BFFF');
            root.style.setProperty('--m-background-color', '#232323');
            root.style.setProperty('--m-text-color', '#D9DDDE');
            root.style.setProperty('--m-sidebar-background', '#313131');
            root.style.setProperty('--m-code-background', '#2A2A2A');
            root.style.setProperty('--m-navbar-background', '#2D2D2D');
            root.style.setProperty('--m-footer-background', '#343434');
        } else if (theme === 'light') {
            root.style.setProperty('--m-primary', '#0099CC');
            root.style.setProperty('--m-background-color', '#D0D9E2');
            root.style.setProperty('--m-text-color', '#212526');
            root.style.setProperty('--m-sidebar-background', '#EFF2F5');
            root.style.setProperty('--m-code-background', '#DFE5EC');
            root.style.setProperty('--m-navbar-background', '#E5E9ED');
            root.style.setProperty('--m-footer-background', '#CBD3DC');
        }

        // Switch logo based on theme
        const logoImg = document.querySelector('.m-image');
        if (logoImg) {
            if (theme === 'light') {
                logoImg.src = logoImg.src.replace('CubosLogoDarkMode.png', 'CubosLogoLightMode.png');
            } else {
                logoImg.src = logoImg.src.replace('CubosLogoLightMode.png', 'CubosLogoDarkMode.png');
            }
        }

        // Force all elements to update their styles
        document.body.style.display = 'none';
        void document.body.offsetHeight;
        document.body.style.display = '';

        // Update document background and colors
        document.documentElement.style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--m-background-color');
        document.body.style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--m-background-color');
        document.body.style.color = getComputedStyle(document.documentElement).getPropertyValue('--m-text-color');

        // Force redraw of themed elements
        const themedElements = document.querySelectorAll('.m-container-inflate, .m-scroll, .m-navbar, .m-sidebar, .m-content, .m-doc-content, pre.m-code');
        themedElements.forEach(el => {
            el.style.display = 'none';
            void el.offsetHeight;
            el.style.display = '';
        });
    }
});
