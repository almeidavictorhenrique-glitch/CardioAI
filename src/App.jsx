import { Routes, Route } from "react-router-dom";

import Login from "./pages/Login";
import Dashboard from "./pages/Dashboard";
import Pacientes from "./pages/Pacientes";
import Agendamentos from "./pages/Agendamentos";

import ProtectedRoute from "./components/ProtectedRoute";

function App() {
  return (
    <Routes>

      {/* Página pública */}
      <Route path="/login" element={<Login />} />

      {/* Páginas protegidas */}
      <Route element={<ProtectedRoute />}>

        <Route path="/" element={<Dashboard />} />

        <Route path="/dashboard" element={<Dashboard />} />

        <Route path="/pacientes" element={<Pacientes />} />

        <Route
          path="/agendamentos"
          element={<Agendamentos />}
        />

      </Route>

    </Routes>
  );
}

export default App;