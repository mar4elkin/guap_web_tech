'use client'

import { ItemBannerCarousel } from '@/app/components/carousel';
import { Button } from '@/app/components/general'
import { useRouter } from 'next/navigation'

const fakeItem = {
  id: 1,
  price: 2500, 
  text: {
    title: "Kingdom Come: Deliverance II",
    shortDescription: `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
    действие которого  разворачивается в Европе XV века. 
    Взгляните на средневековую жизнь  глазами молодого Индржиха, 
    отправившись в путешествие эпического  масштаба.`,
    longDescription: [
      `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`,
      `Захватывающий сюжетный ролевой экшен с богатым открытым миром, 
      действие которого  разворачивается в Европе XV века. 
      Взгляните на средневековую жизнь  глазами молодого Индржиха, 
      отправившись в путешествие эпического  масштаба.`
    ]
  },
  img: {
    previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
    bannerImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg"
  }
}

const ItemsImages = [
    {
      img: {
        previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
        bannerImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg"
      }
    },
    {
      img: {
        previewImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg",
        bannerImg: "https://cdn1.epicgames.com/95d0b9561be1464cb43bd029e94cf526/offer/GR_Epic_Landscape_Offer2560x1440-2560x1440-08987c0c3e1701ea6a7217ed5616922d.jpg"
      }
    }
]

export default function Page() {
    return (
      <>
        <div className="flex lg:flex-row flex-col mt-10">
          <div className="lg:w-4/6 w-full">
            <h2 className="text-4xl font-medium text-text-100 mb-4">{fakeItem.text.title}</h2>
            <ItemBannerCarousel items={ItemsImages} />
          </div>
          <div className="flex flex-col lg:m-5 p-4 grow">
              <h2 className="text-4xl font-medium text-text-100 mt-4 text-center">{fakeItem.price} RUB</h2>
              <div className="flex flex-col justify-between mt-4">
                <Button href={'/cart/1'} text={'Купить'} color={'bg-highlight'} />
                <Button href={'/cart/add/1'} text={'В корзину'} color={'bg-text-100'} />
              </div>
          </div>
        </div>
        <div className="mt-10 w-5/6 m-auto">
          <p className="text-text-100 text-xl font-thin" style={{textWrap: 'pretty', lineBreak: 'normal'}}>
            {fakeItem.text.longDescription.map((item, index) => (
              <>
                {item}
                <br />
                <br />
              </>
            ))}
            </p>
        </div>
      </>
    )
}