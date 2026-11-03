import { createContext, useContext, useState } from "react";

const AuthContext = createContext();

export function AuthProvider({ children }) {
  const [usuario, setUsuario] = useState(() => {
    const usuarioSalvo = localStorage.getItem("cardioia_usuario");

    return usuarioSalvo ? JSON.parse(usuarioSalvo) : null;
  });

  function login(email, senha) {
    // Autenticação simulada
    if (email === "admin@cardioia.com" && senha === "123456") {
      const usuarioFake = {
        nome: "Administrador CardioIA",
        email: email,
      };

      // JWT fake apenas para simulação
      const tokenFake = "cardioia-jwt-token-123456";

      localStorage.setItem("cardioia_token", tokenFake);
      localStorage.setItem(
        "cardioia_usuario",
        JSON.stringify(usuarioFake)
      );

      setUsuario(usuarioFake);

      return true;
    }

    return false;
  }

  function logout() {
    localStorage.removeItem("cardioia_token");
    localStorage.removeItem("cardioia_usuario");

    setUsuario(null);
  }

  const autenticado = usuario !== null;

  return (
    <AuthContext.Provider
      value={{
        usuario,
        autenticado,
        login,
        logout,
      }}
    >
      {children}
    </AuthContext.Provider>
  );
}

export function useAuth() {
  return useContext(AuthContext);
}