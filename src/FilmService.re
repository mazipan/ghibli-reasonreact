open Model;


let fetchData = (~remoteUrl, ~decoder, ~callback) => {
    Js.Promise.(
    Fetch.fetch(remoteUrl)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> decoder
         |> (
           data => {
             callback(data);
             resolve();
           }
         )
       )
    |> ignore
  );
}

