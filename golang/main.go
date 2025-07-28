package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

type HealthResponse struct {
	Language string `json:"language"`
	Version  string `json:"version"`
}

func health(c *gin.Context) {
	response := HealthResponse{
		Language: "go",
		Version:  "1.0.0",
	}
	c.JSON(http.StatusOK, response)
}

func main() {
	r := gin.Default()
	r.GET("/health", health)
	r.Run(":8080")
}
