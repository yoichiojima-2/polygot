import tomllib
from pathlib import Path
from fastapi import FastAPI
from pydantic import BaseModel


app = FastAPI()


def get_version():
    pyproject_path = Path(__file__).parent / "pyproject.toml"
    with pyproject_path.open("rb") as f:
        data = tomllib.load(f)
    return data["project"]["version"]



@app.get("/")
async def health():
    return {
        "language": "python",
        "version": get_version()
    }



if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
