'use client'

import { ItemBannerCarousel } from '@/app/components/carousel';
import { Button } from '@/app/components/general';
import { useRouter, useParams } from 'next/navigation';
import { useEffect, useState } from 'react';

export default function Page() {
  const [game, setGame] = useState({});
  const [loading, setLoading] = useState(true);
  const params = useParams()

  function convertToBanners(game) {
    let itemsImages = []
    game.img.bannerImgs.forEach(el => {
      itemsImages.push(
        {
          img: {
            bannerImgs: el
          }
        }
      )
    });
    return itemsImages;
  }

  useEffect(() => {
    async function fetchData() {
      const res = await fetch(`http://127.0.0.1:1488/game/${params.id}`);
      const data = await res.json();

      setGame(data);
      setLoading(false);
    }
    fetchData();
  }, []);

  return (
    <>
    {loading ? <div>Loading...</div> : 
      <>
        <div className="flex lg:flex-row flex-col mt-10">
          <div className="lg:w-4/6 w-full">
            <h2 className="text-4xl font-medium text-text-100 mb-4">{game.text.title}</h2>
            <ItemBannerCarousel items={convertToBanners(game)} />
          </div>
          <div className="flex flex-col lg:m-5 p-4 grow">
              <h2 className="text-4xl font-medium text-text-100 mt-4 text-center">{game.price} RUB</h2>
              <div className="flex flex-col justify-between mt-4">
                <Button href={`/cart/${game.id}`} text={'Купить'} color={'bg-highlight'} />
                <Button href={`/cart/add/${game.id}`} text={'В корзину'} color={'bg-text-100'} />
              </div>
          </div>
        </div>
        <div className="mt-10 w-5/6 m-auto">
          <p className="text-text-100 text-xl font-thin" style={{textWrap: 'pretty', lineBreak: 'normal'}}>
            {game.text.longDescription.map((item, index) => (
              <>
                {item}
                <br />
                <br />
              </>
            ))}
            </p>
        </div>
      </>
     }
    </>
  )
}