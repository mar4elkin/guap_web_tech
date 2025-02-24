"use client"

import { useState, useEffect } from 'react';
import { useRouter } from 'next/navigation'

export function Button({ href, text, color }) {
    const router = useRouter()
    return (
        <button 
            className={`${color} rounded-lg pt-2 pb-2 pl-5 pr-5 mt-5 text-2xl font-normal text-text_invert-100`}
            onClick={() => router.push(href)}
        >
            {text}
        </button>
    );
}

export function Category({title, items}) {
    return (
        <div className="flex flex-col justify-around mt-10 p-5">
            <h1 className="text-3xl font-bold text-text-100 ">{title}</h1>
            <div className="flex flex-row justify-around mt-10 p-5 flex-wrap">
                {items.map((item, index) => (
                    <PreviewItem item={item} key={index} />
                ))}
            </div>
        </div>
    );
}

export function PreviewItem({ item }) {
    const router = useRouter()
    return (
      <div 
            className="w-48 h-80 overflow-hidden flex flex-col m-4" 
            style={{cursor: 'pointer'}}
            onClick={() => 
                router.push(`/item/${[item.id]}`)
            }
        > 
        {/* w-[205px] h-[280px] */}
            <img 
            className="w-full h-full object-cover rounded-xl" 
            src={item.img.previewImg ? item.img.previewImg : "https://placehold.co/400x600"} 
            alt={item.title || "Preview"} 
            />
            <h1 className="text-xl font-medium text-text-100">{item.text.title}</h1>
            <h2 className="text-lg font-thin text-text-100">{item.price} RUB</h2>
        </div>
    );
  }

export function CartItem({ item }) {
    return (
        <div className="bg-paper flex flex-row p-10 rounded-xl mt-6">
            <img className="w-40 h-64 object-cover rounded-xl" src={item.img.previewImg ? item.img.previewImg : "https://placehold.co/400x600"}  />
            <div className="flex flex-col  w-4/6 p-4">
                <h2 className="text-2xl font-medium text-text-100">{item.text.title}</h2>
                <h3 className="text-2xl font-medium text-text-100">{item.price} RUB</h3>
            </div>
        </div>
    )
}

export function CartView({ items }) {
    const [price, setPrice] = useState(0);
    useEffect(() => {
        let _price = 0
        items.forEach(el => {
            _price += el.price 
        })
        setPrice(_price)
    }, []);

    return (
        <div className="lg:w-5/6 m-auto">
            <div className="flex lg:flex-row flex-col w-full justify-between">
                <div className="flex flex-col lg:w-4/6 w-full p-4">
                    {items.map((item, index) => (
                        <CartItem item={item} key={index} />
                    ))}
                </div>
                <div className="flex flex-col w-ful p-4 grow">
                    <h2 className="text-4xl font-medium text-text-100 mt-4">Итог:</h2>
                    <div className="flex flex-row justify-between mt-4">
                        <h2 className="text-2xl font-medium text-text-100">Цена</h2>
                        <h2 className="text-xl font-tinh text-text-100">{price} RUB</h2>
                    </div>
                    <Button href={`/`} text={'Купить'} color={'bg-text-100'} />
                </div>
            </div>
        </div>
    )
}