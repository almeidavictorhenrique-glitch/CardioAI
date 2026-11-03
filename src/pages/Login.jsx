import { useState } from "react";
import { useNavigate } from "react-router-dom";
import { useAuth } from "../contexts/AuthContext";

export default function Login() {
  const [email, setEmail] = useState("");
  const [senha, setSenha] = useState("");
  const [erro, setErro] = useState("");

  const { login } = useAuth();
  const navigate = useNavigate();

  function handleSubmit(event) {
    event.preventDefault();

    const sucesso = login(email, senha);

    if (sucesso) {
      navigate("/dashboard");
    } else {
      setErro("E-mail ou senha incorretos.");
    }
  }

  return (
    <div className="login-container">

      <div className="login-card">

        <h1>❤️ CardioIA</h1>

        <p>
          Portal de apoio ao diagnóstico cardiológico
        </p>

        <form onSubmit={handleSubmit}>

          <label>E-mail</label>

          <input
            type="email"
            placeholder="Digite seu e-mail"
            value={email}
            onChange={(event) => setEmail(event.target.value)}
          />

          <label>Senha</label>

          <input
            type="password"
            placeholder="Digite sua senha"
            value={senha}
            onChange={(event) => setSenha(event.target.value)}
          />

          {erro && (
            <p className="erro">
              {erro}
            </p>
          )}

          <button type="submit">
            Entrar
          </button>

        </form>

        <small>
          Acesso de demonstração: admin@cardioia.com / 123456
        </small>

      </div>

    </div>
  );
}