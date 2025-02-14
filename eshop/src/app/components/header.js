"use client"

import { useState, useRef, useEffect } from 'react';
import Link from 'next/link'
import { useRouter } from 'next/router'
import BurgerSVG from "../../../public/Burger.svg";
import SearchSVG from "../../../public/Search.svg";
import Image from "next/image";

function SearchBar() {
    return (
        <input className="bg-paper self-center rounded-lg w-3/6 text-2xl font-light text-text-200" placeholder=" поиск" />
    );
}

function MobileMenu() {
    const [isOpen, setIsOpen] = useState(false);
    const dropdownRef = useRef(null);
  
    useEffect(() => {
      const handleClickOutside = (event) => {
        if (dropdownRef.current && !dropdownRef.current.contains(event.target)) {
          setIsOpen(false);
        }
      };
  
      document.addEventListener('mousedown', handleClickOutside);
      return () => {
        document.removeEventListener('mousedown', handleClickOutside);
      };
    }, []);
    return (
        <>
            <Image
                className="h-8 self-center justify-self-end"
                aria-expanded={isOpen}
                onClick={() => setIsOpen(!isOpen)}
                aria-haspopup="true"
                src={BurgerSVG}
                style={{
                    filter: 'invert(100%)',
                    cursor: 'pointer'
                }}
            />
            {isOpen && (
                <div
                    className="absolute right-48 w-80 xl:mt-2 mt-12 origin-top-right bg-highlight rounded-md shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none"
                    role="menu"
                    aria-orientation="vertical"
                    aria-labelledby="menu-button"
                    ref={dropdownRef}
                    style={{zIndex: '99'}}
                >
                    <div className="py-1" role="none">
                        <a
                            href="#"
                            className="block px-4 py-2 text-sm text-text-100 hover:bg-gray-100 hover:text-gray-900"
                            role="menuitem"
                        >
                        Account settings
                        </a>
                        <a
                            href="#"
                            className="block px-4 py-2 text-sm text-text-100 hover:bg-gray-100 hover:text-gray-900"
                            role="menuitem"
                        >
                        Support
                        </a>
                        <a
                            href="#"
                            className="block px-4 py-2 text-sm text-text-100 hover:bg-gray-100 hover:text-gray-900"
                            role="menuitem"
                        >
                        License
                        </a>
                        <form method="POST" action="#" role="none">
                        <button
                            type="submit"
                            className="block w-full px-4 py-2 text-sm text-left text-text-100 hover:bg-gray-100 hover:text-gray-900"
                            role="menuitem"
                        >
                            Sign out
                        </button>
                        </form>
                    </div>
                </div>
            )}
        </>
    );
}

function ProfileMini() {
    const [isOpen, setIsOpen] = useState(false);
    const dropdownRef = useRef(null);
  
    useEffect(() => {
      const handleClickOutside = (event) => {
        if (dropdownRef.current && !dropdownRef.current.contains(event.target)) {
          setIsOpen(false);
        }
      };
  
      document.addEventListener('mousedown', handleClickOutside);
      return () => {
        document.removeEventListener('mousedown', handleClickOutside);
      };
    }, []);

    return (
        <>
            <img 
                className="h-12 self-center justify-self-end clip-your-needful-style" 
                src="https://www.hww.ca/wp-content/uploads/2018/10/Raven-Keith-Williams.jpg" 
                onClick={() => setIsOpen(!isOpen)}
                aria-expanded={isOpen}
                aria-haspopup="true"
                style={{
                    cursor: 'pointer'
                }}
            />
            {isOpen && (
                <div
                    className="absolute right-32 w-56 xl:mt-2 mt-12 origin-top-right bg-highlight rounded-md shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none"
                    role="menu"
                    aria-orientation="vertical"
                    aria-labelledby="menu-button"
                    ref={dropdownRef}
                    style={{zIndex: '99'}}
                >
                    <div className="py-1" role="none">
                        <button
                            type="submit"
                            className="block w-full px-4 py-2 text-sm text-left text-text-100 hover:bg-gray-100 hover:text-gray-900"
                            role="menuitem"
                        >
                            Sign out
                        </button>
                    </div>
                </div>
            )}
        </>
    );
}

export default function Header() {
    return (
        <div className="header flex bg-highlight rounded-xl grow h-20 mt-5 flex-row justify-evenly">
            <div className=" flex self-center flex flex-row w-5/6 justify-between">
                <div className="self-center justify-center mr-4">
                    <Link href="/"><h1 className="text-4xl font-bold text-text-100">gShop</h1></Link>
                </div>
                {/* <SearchBar /> */}
                <div className="self-center justify-center flex flex-row w-2/6 sm:w-1/6 sm:justify-between justify-around">   
                    {/* <h1 className="self-center justify-self-end text-2xl font-medium text-text-100">menu</h1> */}
                    <MobileMenu />
                    <ProfileMini />
                </div>
            </div>
        </div>
    );
}