const SERVER_URL = "10.0.0.32";

export const getMotorSpeed = () =>
  fetch(`http://${SERVER_URL}/speed`).then((res) => res.json());

export const getDirection = () =>
  fetch(`http://${SERVER_URL}/direction`).then((res) => res.json());

export const getRevolutions = (direction) =>
  fetch(
    `http://${SERVER_URL}/revolutions${
      direction === "CW" || direction === "CCW" ? `?direction=${direction}` : ""
    }`
  ).then((res) => res.json());

export const setSpeed = (speed) =>
  fetch(`http://${SERVER_URL}/speed=${speed}`, { method: "POST" }).then((res) =>
    res.json()
  );

export const setDirection = (direction) =>
  fetch(`http://${SERVER_URL}/direction=${direction}`, { method: "POST" }).then(
    (res) => res.json()
  );

export const deleteRevolutions = () =>
  fetch(`http://${SERVER_URL}/revolutions`, { method: "DELETE" }).then((res) =>
    res.json()
  );
