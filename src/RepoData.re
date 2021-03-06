open Json.Decode;

type repo = {
  key: string,
  full_name: string,
  stargazer_count: int,
  html_url: string
};

let parseRepoJson = (json: Js.Json.t): repo => {
  key: string_of_int(field("id", int, json)),
  full_name: field("full_name", string, json),
  stargazer_count: field("stargazers_count", int, json),
  html_url: field("html_url", string, json)
};

let parseReposResponseJson = json => {
  Json.Decode.field("items", Json.Decode.array(parseRepoJson), json);
}

let reposUrl = "https://api.github.com/search/repositories?q=topic%3Areasonml&type=Repositories";

let fetchRepos = () => {
  Js.Promise.(
    Bs_fetch.fetch(reposUrl)
      |> then_(Bs_fetch.Response.text)
      |> then_((jsonText) => {
          resolve(parseReposResponseJson(Js.Json.parseExn(jsonText)));
        })
  )
};