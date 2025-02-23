'use client'

import { useState, useEffect } from "react";
import { useAuth } from "../context/AuthContext";
import { useRouter } from 'next/navigation';

export default function Signup() {
  const router = useRouter();
  const { register, isAuthenticated } = useAuth();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [image, setImage] = useState(null);
  const [preview, setPreview] = useState(null);
  const [loading, setLoading] = useState(false);

  const handleImageChange = (e) => {
    const file = e.target.files[0];
    if (file) {
      setImage(file);
      setPreview(URL.createObjectURL(file));
    }
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!username || !password) return alert("Заполните все поля");
    
    const formData = new FormData();
    formData.append("username", username);
    formData.append("password", password);
    if (image) {
      formData.append("profile_image", image);
    }

    setLoading(true);

    try {
      const response = await fetch("http://127.0.0.1:1488/user/singup", {
        method: "POST",
        body: formData,
      });

      const data = await response.json();

      if (data.status === "ok") {
        register(data.id, data.username, data.password, data.profile_image);
        router.push("/");
      } else {
        alert("Ошибка при регистрации");
      }
    } catch (error) {
      console.error("Ошибка запроса:", error);
      alert("Ошибка соединения с сервером");
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    if (isAuthenticated) {
      router.push("/");
    }
  }, [isAuthenticated, router]);

  return (
    <div className="min-h-screen flex items-center justify-center">
      <div className="bg-highlight p-6 rounded-lg shadow-md w-96">
        <h2 className="text-2xl font-bold mb-4 text-center text-text-100">Регистрация</h2>
        <form onSubmit={handleSubmit} className="flex flex-col gap-4">
          <input
            type="text"
            placeholder="Логин"
            className="p-2 border rounded"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
          />
          <input
            type="password"
            placeholder="Пароль"
            className="p-2 border rounded"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
          />
          <input type="file" onChange={handleImageChange} className="p-2 border rounded" />
          {preview && <img src={preview} alt="Preview" className="w-20 h-20 rounded-full mx-auto" />}
          <button type="submit" className="bg-blue-500 text-white p-2 rounded hover:bg-blue-600">
            Зарегистрироваться
          </button>
        </form>
      </div>
    </div>
  );
}
