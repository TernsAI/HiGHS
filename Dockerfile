FROM eclipse-temurin:17

RUN apt-get update && apt-get install -y \
    build-essential unzip git
RUN wget -O - https://github.com/Kitware/CMake/releases/download/v3.25.0-rc2/cmake-3.25.0-rc2-linux-x86_64.sh | bash -s --skip-license

ADD /HiGHS.zip /
RUN unzip HiGHS.zip -d /HiGHS
RUN mkdir HiGHS/build && \
        cd HiGHS/build && \
        cmake -DFAST_BUILD=ON .. && \
        cmake --build .

# folders should have the 775 permission, which is the minimum allowed permissions to write the files within the API
RUN mkdir HiGHS/build/bin/input && \
        mkdir HiGHS/build/bin/output && \
        chmod 775 HiGHS/build/bin/input && \
        chmod 775 HiGHS/build/bin/output
ENTRYPOINT ["tail", "-f", "/dev/null"]
