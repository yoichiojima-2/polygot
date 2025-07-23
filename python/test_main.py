from . import main
from fastapi.testclient import TestClient

def test_get_version():
    print(main.get_version())


def test_health():
    res = TestClient(main.app).get("/")
    assert res.status_code == 200
    data = res.json()
    assert "version" in data
    assert data["language"] == "python"
