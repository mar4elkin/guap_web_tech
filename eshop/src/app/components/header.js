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
                className="self-center justify-self-end cursor-pointer h-8"
                aria-expanded={isOpen}
                onClick={() => setIsOpen(!isOpen)}
                aria-haspopup="true"
                src={BurgerSVG}
                style={{
                    filter: 'invert(100%)'
                }}
            />
            <div className="relative">
                {isOpen && (
                    <div
                        className="absolute right-0 top-full mt-1 w-80 origin-top-right bg-highlight rounded-md shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none z-50"
                        role="menu"
                        ref={dropdownRef}
                    >
                        <div className="py-1">
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
            </div>
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
                className="clip-your-needful-style cursor-pointer h-12" 
                src="https://www.hww.ca/wp-content/uploads/2018/10/Raven-Keith-Williams.jpg" 
                onClick={() => setIsOpen(!isOpen)}
                aria-expanded={isOpen}
                aria-haspopup="true"
                />
            <div className="relative"> {/* Добавляем контейнер-якорь */}
                {isOpen && (
                    <div
                        className="absolute right-0 top-full mt-1 w-56 origin-top-right bg-highlight rounded-md shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none z-50"
                        role="menu"
                        ref={dropdownRef}
                    >
                        <div className="py-1">
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
            </div>
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
                <div className="self-center justify-center flex flex-row w-2/6 sm:w-1/6 sm:justify-between justify-around aligin-center">   
                    {/* <h1 className="self-center justify-self-end text-2xl font-medium text-text-100">menu</h1> */}
                    <MobileMenu />
                    <ProfileMini />
                </div>
            </div>
        </div>
    );
}