/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./src/pages/**/*.{js,ts,jsx,tsx,mdx}",
    "./src/components/**/*.{js,ts,jsx,tsx,mdx}",
    "./src/app/**/*.{js,ts,jsx,tsx,mdx}",
  ],
  theme: {
    extend: {
      colors: {
        background: "#121212",
        highlight: "#805EAA",
        paper: "#1D1D1D",
        text: {
          100: "#FFFFFF",
          200: "#AAAAAA"
        },
        text_invert: {
          100: "#000000"
        }
      },
    },
  },
  plugins: [],
};
