#include "../inc/parser.hpp"

void HtmlParser::extract_urls(GumboNode* node, std::vector<std::string>& urls) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    GumboAttribute* href;
    if (node->v.element.tag == GUMBO_TAG_A &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
        urls.push_back(href->value);
    }
    const GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        extract_urls(static_cast<GumboNode*>(children->data[i]), urls);
    }
}

void HtmlParser::extract_text(GumboNode* node, std::string& output) {
    if (node->type == GUMBO_NODE_TEXT) {
        output.append(node->v.text.text);
        output.append(" ");
    } else if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag != GUMBO_TAG_SCRIPT && node->v.element.tag != GUMBO_TAG_STYLE) {
        const GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            extract_text(static_cast<GumboNode*>(children->data[i]), output);
        }
    }
}

std::vector<std::string> HtmlParser::split_words(const std::string& text) {
    std::vector<std::string> words;
    std::string word;
    for (char c : text) {
        if (std::isalnum(c)) {
            word += c;
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

void HtmlParser::parse_html(const std::string& html, std::vector<std::string>& urls, std::vector<std::string>& words) {
    GumboOutput* output = gumbo_parse(html.c_str());
    
    extract_urls(output->root, urls);

    std::string text;
    extract_text(output->root, text);
    words = split_words(text);

    gumbo_destroy_output(&kGumboDefaultOptions, output);
}
