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
    | Error

type state = status;

  type action =
    | FetchRequested
    | FetchFailed(status)
    | FetchSucceed(C.response);



let component = ReasonReact.reducerComponent("Query_Get_HOC")

let make = (~remoteUrl, ~decoder, ~onFailure=?, ~onSuccess=?,
 children) => {
    ...component,
    initialState: () => Idle,
    didMount: self => {
      self.send(FetchRequested)
      
    },
    reducer: (action, state) => {
        switch (action) {
                | FetchRequested =>
                    ReasonReact.UpdateWithSideEffects(
                    Loading, ({send}) => {
            Js.Promise.(
                            Bs_fetch.fetch(remoteUrl)
                |> then_(Fetch.Response.json)
                |> then_(json =>
                    json
                    |> decoder
                    |> (
                    data => {
                        send(FetchSucceed(data)) |> resolve
                    }
                    )
                )
                |> catch(e => send(FetchFailed(Error)) |> resolve)
                |> ignore)
                    })
      | FetchSucceed(newData) => ReasonReact.Update(Loaded(newData))
    | FetchFailed(status) =>  ReasonReact.Update(Error)
      }
    },
    render: ({state, send}) => {
      children(state);
    },

}
}



