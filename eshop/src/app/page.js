'use client'

import { ItemBannerCarousel } from './components/carousel';
import { Category } from './components/general'
import { useRouter } from 'next/navigation'

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
  },
  {
    id: 2,
    price: 2500, 
    text: {
      title: "Kingdom Come: Deliverance II",
      shortDescription: `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      long_description: 123
    },
    img: {
      previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
      bannerImg: "https://cdn.akamai.steamstatic.com/apps/csgo/images/csgo_react/social/cs2.jpg"
    }
  },
  {
    id: 3,
    price: 2500, 
    text: {
      title: "Kingdom Come: Deliverance II",
      shortDescription: `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      long_description: 123
    },
    img: {
      previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
      bannerImg: "https://cdn1.epicgames.com/offer/carnation/Share_Image_1920x1080-3_1920x1080-6e2d079f24db0a35285007191358978b"
    }
  },
  {
    id: 4,
    price: 2500, 
    text: {
      title: "Kingdom Come: Deliverance II",
      shortDescription: `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      long_description: 123
    },
    img: {
      previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
      bannerImg: "https://cdn1.epicgames.com/offer/carnation/Share_Image_1920x1080-3_1920x1080-6e2d079f24db0a35285007191358978b"
    }
  },
  {
    id: 5,
    price: 2500, 
    text: {
      title: "Kingdom Come: Deliverance II",
      shortDescription: `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      long_description: 123
    },
    img: {
      previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
      bannerImg: "https://cdn1.epicgames.com/offer/carnation/Share_Image_1920x1080-3_1920x1080-6e2d079f24db0a35285007191358978b"
    }
  }
]

export default function Home() {
  const router = useRouter()
  return (
    <>
      <ItemBannerCarousel items={fakeItems} />
      <Category title={"Category title"} items={fakeItems} />
      <Category title={"Category title"} items={fakeItems} />
      <Category title={"Category title"} items={fakeItems} />
    </>
  );
}
