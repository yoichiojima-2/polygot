const express = require("express");

const PORT = "8080";
const VERSION = "1.0.0";

const health = (req, res) => {
  const response = {
    language: "js",
    version: VERSION,
  };
  res.status(200).json(response);
};

const app = express();

app.get("/health", health);

app.listen(PORT, () => {
  console.log(`server running on port ${PORT}`);
});
