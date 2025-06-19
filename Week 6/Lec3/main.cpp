#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

using namespace std;

class HttpRequest {
private:
    string url;
    string method;
    map<string, string> headers;
    map<string, string> queryParams;
    string body;
    int timeout;

    HttpRequest() { }

public:
    friend class HttpRequestBuilder;
    friend class HttpRequestStepBuilder;

    void execute() {
        cout << "Executing " << method << " request to " << url << endl;

        if (!queryParams.empty()) {
            cout << "Query Parameters:\n";
            for (const auto& param : queryParams) {
                cout << "  " << param.first << "=" << param.second << endl;
            }
        }

        cout << "Headers:\n";
        for (const auto& header : headers) {
            cout << "  " << header.first << ": " << header.second << endl;
        }

        if (!body.empty()) {
            cout << "Body: " << body << endl;
        }

        cout << "Timeout: " << timeout << " seconds\n";
        cout << "Request executed successfully!\n";
    }
};

// --- Builder Pattern ---
class HttpRequestBuilder {
private:
    HttpRequest req;

public:
    HttpRequestBuilder& withUrl(const string& u) {
        req.url = u; return *this;
    }

    HttpRequestBuilder& withMethod(const string& method) {
        req.method = method; return *this;
    }

    HttpRequestBuilder& withHeader(const string& key, const string& value) {
        req.headers[key] = value; return *this;
    }

    HttpRequestBuilder& withQueryParams(const string& key, const string& value) {
        req.queryParams[key] = value; return *this;
    }

    HttpRequestBuilder& withBody(const string& body) {
        req.body = body; return *this;
    }

    HttpRequestBuilder& withTimeout(int timeout) {
        req.timeout = timeout; return *this;
    }

    HttpRequest build() {
        if (req.url.empty()) throw runtime_error("URL cannot be empty");
        return req;
    }
};

// --- Director Pattern ---
class HttpRequestDirector {
public:
    static HttpRequest createGetRequest(const string& url) {
        return HttpRequestBuilder().withUrl(url).withMethod("GET").build();
    }

    static HttpRequest createJsonPostRequest(const string& url, const string& jsonBody) {
        return HttpRequestBuilder()
            .withUrl(url)
            .withMethod("POST")
            .withHeader("Content-Type", "application/json")
            .withHeader("Accept", "application/json")
            .withBody(jsonBody)
            .build();
    }
};

// --- Step Builder Pattern ---
class MethodStep;
class HeaderStep;
class OptionalStep;

class UrlStep {
public:
    virtual MethodStep& withUrl(const string& url) = 0;
};

class MethodStep {
public:
    virtual HeaderStep& withMethod(const string& method) = 0;
};

class HeaderStep {
public:
    virtual OptionalStep& withHeader(const string& key, const string& value) = 0;
};

class OptionalStep {
public:
    virtual OptionalStep& withBody(const string& body) = 0;
    virtual OptionalStep& withTimeout(int timeout) = 0;
    virtual HttpRequest build() = 0;
};

class HttpRequestStepBuilder :
    public UrlStep,
    public MethodStep,
    public HeaderStep,
    public OptionalStep {

private:
    HttpRequest req;

public:
    MethodStep& withUrl(const string& url) override {
        req.url = url; return *this;
    }

    HeaderStep& withMethod(const string& method) override {
        req.method = method; return *this;
    }

    OptionalStep& withHeader(const string& key, const string& value) override {
        req.headers[key] = value; return *this;
    }

    OptionalStep& withBody(const string& body) override {
        req.body = body; return *this;
    }

    OptionalStep& withTimeout(int timeout) override {
        req.timeout = timeout; return *this;
    }

    HttpRequest build() override {
        if (req.url.empty()) throw runtime_error("URL cannot be empty");
        return req;
    }

    static UrlStep& getBuilder() {
        return *(new HttpRequestStepBuilder());
    }
};

// --- Main ---
int main() {
    HttpRequest normalRequest = HttpRequestBuilder()
        .withUrl("https://api.example.com")
        .withMethod("POST")
        .withHeader("Content-Type", "application/json")
        .withHeader("Accept", "application/json")
        .withQueryParams("key", "12345")
        .withBody("{\"name\": \"Aditya\"}")
        .withTimeout(60)
        .build();
    normalRequest.execute();

    cout << "\n----------------------------\n";

    HttpRequest getRequest = HttpRequestDirector::createGetRequest("https://api.example.com/users");
    getRequest.execute();

    cout << "\n----------------------------\n";

    HttpRequest postRequest = HttpRequestDirector::createJsonPostRequest(
        "https://api.example.com/users",
        "{\"name\": \"Aditya\", \"email\": \"aditya@example.com\"}");
    postRequest.execute();

    cout << "\n----------------------------\n";

    HttpRequest stepRequest = HttpRequestStepBuilder::getBuilder()
        .withUrl("https://api.example.com/products")
        .withMethod("POST")
        .withHeader("Content-Type", "application/json")
        .withBody("{\"product\": \"Laptop\", \"price\": 49999}")
        .withTimeout(45)
        .build();
    stepRequest.execute();
}
