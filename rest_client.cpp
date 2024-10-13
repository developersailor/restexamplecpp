#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
int main()
{
    using namespace web;                      // Genel özellikler (URI vs.)
    using namespace web::http;                // HTTP işlevselliği
    using namespace web::http::client;        // HTTP istemcisi özellikleri

    // HTTP istemcisi oluştur
    http_client client(U("https://jsonplaceholder.typicode.com"));

    // İstek URI'sini oluştur
    uri_builder builder(U("/posts/1"));

    // GET isteği gönder
    client.request(methods::GET, builder.to_string())
    .then([](http_response response) {
        // Durum kodunu kontrol et
        if (response.status_code() == status_codes::OK) {
            // Yanıt gövdesini JSON olarak çıkar
            return response.extract_json();
        }
        // Hata durumunda boş JSON döndür
        return pplx::task_from_result(json::value());
    })
    .then([](pplx::task<json::value> previousTask) {
        try {
            // JSON değerini al
            const json::value &v = previousTask.get();

            // JSON değerini yazdır
            std::wcout << U("Başlık: ") << v.at(U("title")).as_string().c_str() << std::endl;
            std::wcout << U("İçerik: ") << v.at(U("body")).as_string().c_str() << std::endl;
        } catch (const http_exception& e) {
            std::wcout << e.what() << std::endl;
        }
    })
    .wait();

    return 0;
}