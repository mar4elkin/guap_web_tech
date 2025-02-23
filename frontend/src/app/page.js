'use client'

import { ItemBannerCarousel } from './components/carousel';
import { Category } from './components/general';
import { useEffect, useState } from 'react';

export default function Home() {
  const [games, setGames] = useState([]);
  const [loading, setLoading] = useState(true);

  const convertGamesToCarouselItems = (games) => {
    return games.map((game, index) => ({
      id: game.id,
      price: game.price,
      text: {
        title: game.text.title,
        shortDescription: game.text.shortDescription,
        longDescription: game.text.longDescription
      },
      img: {
        previewImg: game.img.previewImg,
        bannerImgs: game.img.bannerImgs[0]
      }
    }));
  };

  useEffect(() => {
    async function fetchData() {
      const res = await fetch('http://127.0.0.1:1488/games');
      const data = await res.json();

      setGames(data.games);
      setLoading(false);
    }
    fetchData();
  }, []);

  return (
    <>
      {loading ? <div>Loading...</div> : 
        <>
          <ItemBannerCarousel items={convertGamesToCarouselItems(games)} />
          <Category title={"Category title"} items={games} />
          <Category title={"Category title"} items={games} />
          <Category title={"Category title"} items={games} />
        </>
      }
    </>
  );
}
