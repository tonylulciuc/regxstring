from conans import ConanFile, CMake, tools


class RegxstringConan(ConanFile):
    name = "regxstring"
    version = "0.1"
    license = "Apache License 2.0"
    author = "daidodo"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "This is a Random String Generator based on Regular Expression."
    topics = ("conan", "lexer", "generator")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"
    requires = "pcre/8.44", "gtest/1.10.0"
    exports_sources = "include/*", "src/regxstring_impl.cpp", "src/regxstring.cpp", "CMakeLists.txt"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src=".", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["regxstring"]

