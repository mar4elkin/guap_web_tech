"use client"

import Link from 'next/link'
import ArrowLeft from "../../../public/ArrowLeft.svg";
import ArrowRight from "../../../public/ArrowRight.svg";
import Image from "next/image";
import { Button } from "./general";
import { useState, useEffect } from "react";

export function ItemBannerCarousel({items}) {
    const [bCanSwitch, setBCanSwitch] = useState(true);
    const [currentIndex, setCurrentIndex] = useState(1);
    const [transition, setTransition] = useState(true);
    
    const clonedItems = items.length > 1 
      ? [items[items.length - 1], ...items, items[0]] 
      : items;
  
    const handleTransitionEnd = () => {
      if (items.length <= 1) return;
      
      if (currentIndex === 0) {
        setTransition(false);
        setCurrentIndex(clonedItems.length - 2);
      } else if (currentIndex === clonedItems.length - 1) {
        setTransition(false);
        setCurrentIndex(1);
      }
    };
  
    const prevSlide = () => {
      if (items.length <= 1) return;
      if (bCanSwitch) {
        setBCanSwitch(false);
        setTransition(true);
        setCurrentIndex(prev => prev - 1);
        setTimeout(() => {setBCanSwitch(true)}, 500);
      }
      
    };
  
    const nextSlide = () => {
      if (items.length <= 1) return;
      if (bCanSwitch) {
        setBCanSwitch(false);
        setTransition(true);
        setCurrentIndex(prev => prev + 1);
        setTimeout(() => {setBCanSwitch(true)}, 500);
      }
      
    };
  
    if (items.length === 0) return null;
  
    return (
        <div className="flex flex-row justify-around mt-10">
          <Image src={ArrowLeft} alt={""} onClick={prevSlide} style={{ cursor: 'pointer' }} />
          <div className="w-5/6 m-auto" style={{ overflow: "hidden" }}>
            <div 
              className="w-fill rounded-xl"
              style={{
                height: '450px', 
                overflow: 'hidden', 
                position: 'relative' 
            }}>
              <div
                style={{
                  display: "flex",
                  transform: `translateX(-${currentIndex * (100 / clonedItems.length)}%)`,
                  transition: transition ? "transform 0.5s ease-in-out" : "none",
                  width: `${clonedItems.length * 100}%`,
                  height: '100%'
                }}
                onTransitionEnd={handleTransitionEnd}
              >
                {clonedItems.map((item, index) => (
                  <div 
                    key={index}
                    style={{ 
                      position: 'relative',
                      width: `${100 / clonedItems.length}%`, 
                      flexShrink: 0,
                      height: '100%',
                      borderRadius: '1rem'
                    }}
                  >
                    <img
                      src={item.img.bannerImgs ? "https://placehold.co/400x600": item.img.bannerImgs}
                      alt="banner"
                      style={{ 
                        width: '100%',
                        height: '100%',
                        objectFit: 'cover',
                        borderRadius: 'inherit'
                      }}
                    />
                    {item.text && (
                      <div className="absolute bottom-5 left-5 text-white">
                        <h1 className="text-3xl font-bold" style={{textShadow: '2px 2px 4px rgba(0,0,0,0.5)'}}>{item.text.title}</h1>
                        {item.text.shortDescription && (
                          <p 
                              className="text-base mt-2" 
                              style={{
                                  textShadow: '2px 2px 4px rgba(0,0,0,0.5)',
                                  textWrap: 'pretty'
                              }}
                              >{item.text.shortDescription}
                          </p>
                        )}
                        <Button href={`/item/${item.id}`} text={'Купить'} color={'bg-text-100'} />
                      </div>
                    )}
                  </div>
                ))}
              </div>
            </div>
          </div>
          <Image src={ArrowRight} alt={""} onClick={nextSlide} style={{ cursor: 'pointer' }} />
        </div>
      );
}