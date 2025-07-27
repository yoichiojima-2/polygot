test:
	uv run pytest -vvv .

clean:
	-rm -f uv.lock
	find . -type d -name "__pycache__" -exec rm -rf {} \;
	find . -type d -name ".venv" -exec rm -rf {} \;
	find . -type d -name ".pytest_cache" -exec rm -rf {} \;
