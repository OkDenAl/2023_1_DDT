generate:
	mkdir build
	cmake -B build/
	
build-project:
	cd ./build && cmake .. && make --no-print-directory

clean:
	rm -rf build

rebuild: clean generate build-project

server-run:
	./build/server/cmd/Server

test:
	ctest --verbose --test-dir  build/

check:
	cppcheck server --std=c++17 --enable=all

lint:
	./run_linters.sh

format:
	./run_format.sh

dev:
	docker run --rm -it \
		-v $(PWD):/project \
		--name app \
		-p 8080:8080 \
		raiden454/cpp-app

stop-docker:
	docker stop app

run-docker-compose:
	docker compose up -d --build

