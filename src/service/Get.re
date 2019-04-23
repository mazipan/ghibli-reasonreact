// HOC
// use it 
// <Get remoteUrl="">
//  {({status, data} =>
// }
// </Get>
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
                |> ignore)
}

module type Config = {type response;};

module Make = (C: Config) => {
type response;

type status = 
    | Idle 
    | Loading 
    | Loaded(C.response)
    | Error(string)



  type action =
    | FetchRequested
    | FetchFailed(string)
    | FetchSucceed(C.response);


type state = {
    status,
    data: option(C.response)
};

let component = ReasonReact.reducerComponent("Query_Get_HOC")

let make = (~remoteUrl, ~decoder, ~onFailure=?, ~onSuccess=?,
 children) => {
    ...component,
    initialState: () => { 
        status: Idle,
        data: None
    },
      didMount: self => {
      self.send(FetchRequested)
      
    },
    reducer: (action, state) => {
        switch (action) {
                | FetchRequested =>
                    ReasonReact.UpdateWithSideEffects(
                    {...state, status: Loading}, self => {
            Js.Promise.(
                Fetch.fetch(remoteUrl)
                |> then_(Fetch.Response.json)
                |> then_(json =>
                    json
                    |> decoder
                    |> (
                    data => {
                        self.send(FetchSucceed(data)) |> resolve
                    }
                    )
                )
                |> catch(e => Js.log(e) |> resolve)
                |> ignore)
                    })
              | FetchFailed(message) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, status: Error(message)},
          _self =>
            switch (onFailure) {
            | Some(fn) => fn(message)
            | None => ()
            },
        )
      | FetchSucceed(newData) =>
        ReasonReact.UpdateWithSideEffects(
          {status: Loaded(newData), data: newData->Some},
          _self =>
            switch (onSuccess) {
            | Some(fn) => fn(newData)
            | None => ()
            },
        )

      }
    },
    render: ({state, send}) => {
      children(state.status);
    },

}
}



