'use client'

import { useEffect } from "react";
import { useAuth } from "../context/AuthContext";
import { useRouter } from 'next/navigation';

export default function Signup() {
  const router = useRouter();
  const { isAuthenticated, logout } = useAuth();

  useEffect(() => {
    if (isAuthenticated) {
      logout();
      router.push("/");
    }
  }, [isAuthenticated, router]);

  return (
    <>
    </>
  );
}
