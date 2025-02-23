'use client'

import { CartView } from '@/app/components/general';
import { useRouter, useParams } from 'next/navigation';
import { useEffect, useState } from 'react';

const fakeItems = [
    {
      id: 1,
      price: 2500, 
      text: {
        title: "Kingdom Come: Deliverance II",
        shortDescription: `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
        действие которого  разворачивается в Европе XV века. 
        Взгляните на средневековую жизнь  глазами молодого Индржиха, 
        отправившись в путешествие эпического  масштаба.`,
        longDescription: 123
      },
      img: {
        previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
        bannerImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg"
      }
    }
]

export default function Page() {
  const params = useParams()
  const [game, setGame] = useState([]);
  const [loading, setLoading] = useState(true);

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
      let dataArr = []
      dataArr.push(data)

      setGame(dataArr);
      setLoading(false);
    }
    fetchData();
  }, []);

  return (
    <>
    {loading ? <div>Loading...</div> : 
      <div className="mt-10">
          {game.length > 0 && (
              <CartView items={game} />
          )}
      </div>
      }
    </>
  )
}